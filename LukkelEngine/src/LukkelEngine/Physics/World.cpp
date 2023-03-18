#include "LKpch.h"
#include "LukkelEngine/Physics/World.h"
#include "LukkelEngine/Editor/EditorLayer.h"
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Scene/Components.h"
#include "LukkelEngine/Core/Application.h"
#include "LukkelEngine/Event/ConstraintEvent.h"


namespace LukkelEngine {

	PhysicsDebugger physicsDebugger;
	uint64_t World::s_EntitiesInWorld;
	World* World::m_CurrentWorld;

	World::World()
	{
		s_EntitiesInWorld = 0;
	}

	World::~World()
	{
		shutdownPhysics();
	}

	void World::onUpdate(float ts)
	{
		handleEvents();
		if (!m_Paused)
		{
			checkCollisions();
			m_DynamicWorld->stepSimulation(ts);
			m_DynamicWorld->updateAabbs();
			m_DynamicWorld->computeOverlappingPairs();
		}
	}

	void World::initPhysics(Scene* scene)
	{
		m_BroadphaseInterface = new btDbvtBroadphase();
		m_CollisionConfig = new btDefaultCollisionConfiguration();
		m_Dispatcher = new btCollisionDispatcher(m_CollisionConfig);
		m_SequentialConstraintSolver = new btSequentialImpulseConstraintSolver();

		m_Scene = scene;
		m_DynamicWorld = new btDiscreteDynamicsWorld(m_Dispatcher, m_BroadphaseInterface, m_SequentialConstraintSolver, m_CollisionConfig);
		m_DynamicWorld->setGravity(LK_WORLD_GRAVITY_SLOW);

		physicsDebugger.setDebugMode(btIDebugDraw::DBG_DrawWireframe + btIDebugDraw::DBG_DrawContactPoints + btIDebugDraw::DBG_DrawAabb);
		m_DynamicWorld->setDebugDrawer(&physicsDebugger);
		m_CurrentWorld = this;
	}

	void World::handleEvents()
	{
		for (auto& event : m_Events)
		{
			bool handled = event->handleEvent();
			if (handled) 
			{
				auto it = std::find(m_Events.begin(), m_Events.end(), event);
				m_Events.erase(it);
				LKLOG_INFO("Event handled!");
				delete event;
			}
		}
	}

	void World::onEvent(Event& event)
	{
	}

	void World::shutdownPhysics()
	{
		delete m_DynamicWorld;
		delete m_BroadphaseInterface;
		delete m_CollisionConfig;
		delete m_Dispatcher;
		delete m_SequentialConstraintSolver;
	}

	bool World::pickBody(const Camera& camera, float distance)
	{
		// Cast ray
		auto [rayFrom, rayDir] = CollisionDetector::Raycast(camera);
		btVector3 from = btVector3(rayFrom.x, rayFrom.y, rayFrom.z);
		btVector3 to_dir = btVector3(rayDir.x, rayDir.y, rayDir.z);
		btVector3 to = from + (btVector3(rayDir.x, rayDir.y, rayDir.z) * distance);
		// Perform ray test
		btCollisionWorld::ClosestRayResultCallback rayCallback(from, to);
		m_DynamicWorld->rayTest(from, to, rayCallback);

		// Check if ray has hit something
		if (rayCallback.hasHit())
		{
			btVector3 pickPos = rayCallback.m_hitPointWorld;
			btRigidBody* body = (btRigidBody*)btRigidBody::upcast(rayCallback.m_collisionObject);

			bool picked = false;
			if (body && body->isInWorld())
			{
				// If the hit body is a valid object, continue
				if (!(body->isStaticOrKinematicObject()))
				{
					uint64_t id = (uint64_t)body->getUserPointer();
					auto& pickedEntity = m_Scene->getEntityWithUUID(id);
					if (pickedEntity && pickedEntity != m_PickedEntity)
					{
						// Remove the focus selection from the last picked entity
						m_PickedEntity.isSelected = false;
						// Setup the focus on the newly hit entity
						m_PickedEntity = pickedEntity;
						EditorLayer::m_SelectedEntity = m_PickedEntity;
						pickedEntity.isSelected = true;
						m_PickedBody = body;
						picked = true;
					}
				}
			}

			m_OldPickingPos = to;
			m_HitPos = pickPos;
			m_OldPickingDist = (pickPos - from).length();
			return picked;
		}
		else
		{
			// resetMousePick();
			LKLOG_INFO("");
			return false;
		}
	}

	void World::stepSimulation(float ts)
	{
		m_DynamicWorld->stepSimulation(ts);
	}

	void World::registerEvent(Event* event)
	{
		LKLOG_INFO("Registering event {0}", event->getName());
		m_Events.push_back(event);
	}

	template<typename T>
	void World::addRigidbodyToWorld(T& rigidbody)
	{ 
	}
		template<>
		void World::addRigidbodyToWorld<btRigidBody*>(btRigidBody*& rigidbody)
		{
			m_DynamicWorld->addRigidBody(rigidbody);
			s_EntitiesInWorld++;
		}

		template<>
		void World::addRigidbodyToWorld<Rigidbody>(Rigidbody& rigidbody)
		{
			m_DynamicWorld->addRigidBody(rigidbody.getRigidbody());
			s_EntitiesInWorld++;
		}


	void World::removePickConstraint()
	{
		if (m_PickedConstraint)
		{
			m_PickedBody->forceActivationState(m_SavedState);
			m_PickedBody->activate();
			m_DynamicWorld->removeConstraint(m_PickedConstraint);

			delete m_PickedConstraint;
			m_PickedConstraint = 0;
			m_PickedBody = 0;
		}
	}

	void World::resetMousePick()
	{
		m_PickedBody = nullptr;
		m_PickedEntity = {};
		EditorLayer::m_SelectedEntity = {};
	}

	bool World::mouseButtonCallback(int button, int state, float x, float y)
	{
		float distance = 800.0f;
		if (state == 1)
		{
			if (button == 0)
			{
				bool bodyIsPicked = pickBody(*m_Scene->getCamera(), distance);
				LKLOG_INFO("bodyIsPicked -> {0}", bodyIsPicked);
				if (bodyIsPicked)
				{
					LKLOG_CRITICAL("Body picked -> {0}", m_PickedEntity.getName());
				}
			}
		}

		return false;
	}

	bool World::mouseMoveCallback(float x, float y)
	{
		return false;
	}

	btVector3 World::screenToWorld(float mx, float my, glm::mat4 view, glm::mat4 projection)
	{
		// Get the viewport dimensions
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);

		// Calculate the mouse position in normalized device coordinates
		float ndcX = (2.0f * mx) / viewport[2] - 1.0f;
		float ndcY = 1.0f - (2.0f * my) / viewport[3];
		glm::vec4 ndcPos = glm::vec4(ndcX, ndcY, 0.0f, 1.0f);

		// Convert from normalized device coordinates to world coordinates
		glm::vec4 clipPos = glm::vec4(ndcPos.x, ndcPos.y, -1.0f, 1.0f);
		glm::vec4 eyePos = glm::inverse(projection) * clipPos;
		eyePos = glm::vec4(eyePos.x, eyePos.y, -1.0f, 0.0f);
		glm::vec4 worldPos = glm::inverse(view) * eyePos;

		return btVector3(worldPos.x, worldPos.y, worldPos.z);
	}


	void World::createPickingConstraint(float x, float y)
	{
	}

	void World::addConstraint(Constraint& constraint)
	{
		m_DynamicWorld->addConstraint(constraint.getConstraint());
	}

	void World::removeConstraint(Constraint& constraint)
	{
		m_DynamicWorld->removeConstraint(constraint.getConstraint());
	}

	void World::createCollisionObject(btCollisionObject* body)
	{
		if (body->getUserIndex() < 0)
		{
			btCollisionShape* shape = body->getCollisionShape();
			btTransform startTransform = body->getWorldTransform();
			int graphicsShapeId = shape->getUserIndex();
			if (graphicsShapeId >= 0)
			{
				btVector3 localScaling(1, 1, 1);

				btSoftBody* softBody = btSoftBody::upcast(body);
				if (softBody)
				{
					// ASSERTION HERE
					LKLOG_INFO("SOFTBODY CREATED");
				}
			}
		}
	}

	void World::checkCollisions()
	{
		CollisionPairs collisionPairs;

		if (m_Dispatcher)
		{
			for (int i = 0; i < m_Dispatcher->getNumManifolds(); i++)
			{
				LKLOG_WARN("Creating manifold by index");
				btPersistentManifold* manifold = m_Dispatcher->getManifoldByIndexInternal(i);

				if (manifold->getNumContacts() > 0)
				{
					const btRigidBody* body1 = static_cast<const btRigidBody*>(manifold->getBody0());
					const btRigidBody* body2 = static_cast<const btRigidBody*>(manifold->getBody1());
					bool const swapped = body1 > body2;
					const btRigidBody* sortedBody1 = swapped ? body1 : body2;
					const btRigidBody* sortedBody2 = swapped ? body2 : body1;

					uint64_t id1 = (uint64_t)sortedBody1->getUserPointer();
					uint64_t id2 = (uint64_t)sortedBody2->getUserPointer();
					Entity entity1 = m_Scene->getEntityWithUUID(id1);
					Entity entity2 = m_Scene->getEntityWithUUID(id2);
					LKLOG_TRACE("Entity 1 name: {0}", entity1.getName());
					LKLOG_TRACE("Entity 2 name: {0}", entity2.getName());
					// LKLOG_TRACE("Collision ID 1: {0}", id1);
					// LKLOG_TRACE("Collision ID 2: {0}", id2);
					CollisionPair pair = std::make_pair(sortedBody1, sortedBody2);
					// CollisionPair entityPair = std::make_pair(entity1, entity2);
					// collisionPairs.insert(entityPair);
					collisionPairs.insert(pair);

					// If the collision pair is only found at the last insertion, then it is a new collision
					if (m_LastCollisionPairs.find(pair) == m_LastCollisionPairs.end())
					{ 
						// Trigger collision event
					}
				}
			}
			CollisionPairs removedPairs;

			std::set_difference(m_LastCollisionPairs.begin(), m_LastCollisionPairs.end(),
				collisionPairs.begin(), collisionPairs.end(), std::inserter(removedPairs, removedPairs.begin()));

			// Iterate through removed pairs and trigger separation events
			for (CollisionPairs::const_iterator iter = removedPairs.begin(); iter != removedPairs.end(); iter++)
			{
				LKLOG_TRACE("Trigger Separation Event");
			}

			m_LastCollisionPairs = collisionPairs;
		}
	}

}
