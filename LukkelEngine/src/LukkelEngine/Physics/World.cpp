#include "LKpch.h"
#include "LukkelEngine/Physics/World.h"
#include "LukkelEngine/Editor/EditorLayer.h"
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Scene/Components.h"

#include "LukkelEngine/Core/Application.h"


namespace LukkelEngine {

	PhysicsDebugger physicsDebugger;
	uint64_t World::s_EntitiesInWorld;

	World::World()
	{
		s_EntitiesInWorld = 0;
		LKLOG_INFO("World created");
	}

	World::~World()
	{
		shutdownPhysics();
	}

	void World::onUpdate(float ts)
	{
		// If not paused, simulate the world
		if (!m_Paused)
		{
			m_DynamicWorld->stepSimulation(ts);
			m_DynamicWorld->updateAabbs();
			m_DynamicWorld->computeOverlappingPairs();
		}
		// m_DynamicWorld->debugDrawWorld();
	}

	void World::initPhysics(Scene* scene)
	{
		btBroadphaseInterface* broadphase = new btDbvtBroadphase();
		btDefaultCollisionConfiguration* collisionConfig = new btDefaultCollisionConfiguration();
		btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfig);
		btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

		m_Scene = scene;
		m_DynamicWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);
		m_DynamicWorld->setGravity(LK_WORLD_GRAVITY_SLOW);

		physicsDebugger.setDebugMode(btIDebugDraw::DBG_DrawWireframe + btIDebugDraw::DBG_DrawContactPoints + btIDebugDraw::DBG_DrawAabb);
		m_DynamicWorld->setDebugDrawer(&physicsDebugger);
	}

	void World::shutdownPhysics()
	{
		delete m_DynamicWorld;
		delete m_Broadphase;
		delete m_CollisionConfig;
		delete m_Dispatcher;
		delete m_Solver;
	}

	bool World::pickBody(const Camera& camera, float distance)
	{
		// FIX CAMERA PASSED AS ARGUMENT
		auto cam = camera;
		auto camPos = cam.getPosition();

		auto [rayFrom, rayDir] = raycast(cam);
		btVector3 from = btVector3(rayFrom.x, rayFrom.y, rayFrom.z);
		btVector3 to_dir = btVector3(rayDir.x, rayDir.y, rayDir.z);
		btVector3 to = from + (btVector3(rayDir.x, rayDir.y, rayDir.z) * distance);

		btCollisionWorld::ClosestRayResultCallback rayCallback(from, to);
		m_DynamicWorld->rayTest(from , to, rayCallback);

		if (rayCallback.hasHit())
		{
			btVector3 pickPos = rayCallback.m_hitPointWorld;
			btRigidBody* body = (btRigidBody*)btRigidBody::upcast(rayCallback.m_collisionObject);

			bool picked = false;
			if (body && body->isInWorld())
			{
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
			resetMousePick();
			LKLOG_INFO("");
			return false;
		}
	}

	void World::stepSimulation(float ts)
	{
		m_DynamicWorld->stepSimulation(ts);
	}

	template<typename T>
	void World::addRigidBodyToWorld(T& rigidbody)
	{ 
	}
		template<>
		void World::addRigidBodyToWorld<btRigidBody*>(btRigidBody*& rigidbody)
		{
			m_DynamicWorld->addRigidBody(rigidbody);
			s_EntitiesInWorld++;
		}

		template<>
		void World::addRigidBodyToWorld<RigidBody>(RigidBody& rigidbody)
		{
			m_DynamicWorld->addRigidBody(rigidbody.getRigidBody());
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
		float distance = 800.0f; // FIXME
		if (state == 1)
		{
			if (button == 0)
			{
				bool bodyIsPicked = pickBody(*m_Scene->getCamera(), distance);
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

	bool World::movePickedBody(glm::vec3& rayFrom, glm::vec3& rayTo)
	{
		btVector3 from{ rayFrom.x, rayFrom.y, rayFrom.z };
		btVector3 to{ rayTo.x, rayTo.y, rayTo.z };

		if (m_PickedBody && m_PickedConstraint)
		{
			LKLOG_TRACE("Getting picked constraint");
			btPoint2PointConstraint* pickCon = static_cast<btPoint2PointConstraint*>(m_PickedConstraint);
			LKLOG_WARN("Got picked constraint");
			if (pickCon)
			{
				// Keep it at the same picking distance
				btVector3 newPivotB;

				btVector3 dir = to - from;
				dir.normalize();
				dir *= m_OldPickingDist;

				newPivotB = from + dir;
				pickCon->setPivotB(newPivotB);
				return true;
			}
		}
		return false;
	}

	std::pair<glm::vec3, glm::vec3> World::raycast(const Camera& camera)
	{
		auto [mouseX, mouseY] = Mouse::getMousePosition();
		// auto& cam = camera;
		auto& cam = m_Scene->getCamera();
		auto screenWidth = cam->getScreenWidth();
		auto screenHeight = cam->getScreenHeight();
		auto projection = cam->getProjection();
		auto view = cam->getView();

		// Lock the ray to the middle of the screen, need to fix the GLFW cursor pos 
		mouseX = screenWidth / 2;
		mouseY = screenHeight / 2;

		glm::vec4 rayStart_NDC(
			((float)mouseX/(float)screenWidth  - 0.5f) * 2.0f, // [0,  width] -> [-1,1]
			((float)mouseY/(float)screenHeight - 0.5f) * 2.0f, // [0, height] -> [-1,1]
		   -1.0, // The near plane maps to Z=-1
			1.0f
		);
		glm::vec4 rayEnd_NDC(
			((float)mouseX/(float)screenWidth  - 0.5f) * 2.0f, // * -1 (?)
			((float)mouseY/(float)screenHeight - 0.5f) * 2.0f,
			0.0,
			-1.0f
		);

		glm::mat4 invViewProjection = glm::inverse(projection * view);
		glm::vec4 rayStart_world = invViewProjection * rayStart_NDC;
		glm::vec4 rayEnd_world   = invViewProjection * rayEnd_NDC  ; 
		rayStart_world /= rayStart_world.w;
		rayEnd_world   /= rayEnd_world.w;

		glm::vec3 rayDirection_world(rayEnd_world - rayStart_world);
		rayDirection_world = glm::normalize(rayDirection_world);

		glm::vec3 rayPos = glm::vec3(rayStart_world);
		glm::vec3 rayDir = glm::normalize(rayDirection_world);

		return { rayPos, rayDir };
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

	void World::createPickingConstraint(Entity& entity)
	{
	}

	void World::addConstraint(btTypedConstraint* constraint, btRigidBody* body)
	{
		m_DynamicWorld->addConstraint(constraint, true);
		LKLOG_WARN("New constraint added!");
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

}
