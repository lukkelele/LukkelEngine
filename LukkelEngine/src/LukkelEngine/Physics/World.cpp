#include "LKpch.h"
#include "LukkelEngine/Physics/World.h"
#include "LukkelEngine/Editor/EditorLayer.h"
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Scene/Components.h"
#include "LukkelEngine/Core/Application.h"
#include "LukkelEngine/Event/ConstraintEvent.h"
#include "LukkelEngine/Event/CollisionEvent.h"


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
		ShutdownPhysics();
	}

	void World::OnUpdate(float ts)
	{
		HandleEvents();
		if (!m_Paused)
		{
			CheckCollisions();
			m_DynamicWorld->stepSimulation(ts);
			m_DynamicWorld->updateAabbs();
			m_DynamicWorld->computeOverlappingPairs();
		}
	}

	void World::InitPhysics(Scene* scene)
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

	void World::HandleEvents()
	{
		for (auto& event : m_Events)
		{
			bool handled = event->HandleEvent();
			if (handled) 
			{
				auto it = std::find(m_Events.begin(), m_Events.end(), event);
				m_Events.erase(it);
				LKLOG_INFO("Event handled!");
				delete event;
			}
		}
	}

	void World::OnEvent(Event& event)
	{
	}

	void World::ShutdownPhysics()
	{
		delete m_DynamicWorld;
		delete m_BroadphaseInterface;
		delete m_CollisionConfig;
		delete m_Dispatcher;
		delete m_SequentialConstraintSolver;
	}

	bool World::PickBody(const Camera& camera, float distance)
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

	void World::StepSimulation(float ts)
	{
		m_DynamicWorld->stepSimulation(ts);
	}

	void World::RegisterEvent(Event* event)
	{
		LKLOG_INFO("Registering event {0}", event->GetName());
		m_Events.push_back(event);
	}

	template<typename T>
	void World::AddRigidbodyToWorld(T& rigidbody)
	{ 
	}
		template<>
		void World::AddRigidbodyToWorld<btRigidBody*>(btRigidBody*& rigidbody)
		{
			m_DynamicWorld->addRigidBody(rigidbody);
			s_EntitiesInWorld++;
		}

		template<>
		void World::AddRigidbodyToWorld<Rigidbody>(Rigidbody& rigidbody)
		{
			m_DynamicWorld->addRigidBody(rigidbody.GetRigidbody());
			s_EntitiesInWorld++;
		}


	void World::RemovePickConstraint()
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

	void World::ResetMousePick()
	{
		m_PickedBody = nullptr;
		m_PickedEntity = {};
		EditorLayer::m_SelectedEntity = {};
	}

	bool World::MouseButtonCallback(int button, int state, float x, float y)
	{
		float distance = 800.0f;
		if (state == 1)
		{
			if (button == 0)
			{
				bool bodyIsPicked = PickBody(*m_Scene->getCamera(), distance);
				if (bodyIsPicked)
				{
					LKLOG_CRITICAL("Body picked -> {0}", m_PickedEntity.GetName());
				}
			}
		}

		return false;
	}

	bool World::MouseMoveCallback(float x, float y)
	{
		return false;
	}

	void World::CreatePickingConstraint(float x, float y)
	{
	}

	void World::CheckCollisions()
	{
		CollisionPairs collisionPairs;

		if (m_Dispatcher)
		{
			for (int i = 0; i < m_Dispatcher->getNumManifolds(); ++i)
			{
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

					CollisionPair pair = std::make_pair(sortedBody1, sortedBody2);
					collisionPairs.insert(pair);

					// If the collision pair is only found at the last insertion, then it is a new collision
					// COLLISION EVENT
					if (m_LastCollisionPairs.find(pair) == m_LastCollisionPairs.end())
						RegisterEvent(new CollisionEvent(pair.first, pair.second));
				}
			}

			CollisionPairs removedPairs;

			std::set_difference(m_LastCollisionPairs.begin(), m_LastCollisionPairs.end(),
									collisionPairs.begin(), collisionPairs.end(),
										std::inserter(removedPairs, removedPairs.begin()));

			// Iterate through removed pairs and trigger separation events
			// SEPARATION EVENT
			for (CollisionPairs::const_iterator iter = removedPairs.begin(); iter != removedPairs.end(); ++iter)
				RegisterEvent(new SeparationEvent((const btRigidBody*)iter->first, (const btRigidBody*)iter->second));

			m_LastCollisionPairs = collisionPairs;
		}
	}


	Entity& World::GetEntity(Rigidbody& rigidbody)
	{
		auto currentScene = Scene::GetActiveScene();
		Entity& entity = currentScene->getEntityWithUUID(rigidbody.GetID());
		return entity;
	}

}
