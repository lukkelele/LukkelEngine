#include "LKpch.h"
#include "LukkelEngine/Physics/World.h"
#include "LukkelEngine/Editor/Editor.h"
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Scene/Entity.h"

#include "LukkelEngine/Core/Application.h"


namespace LukkelEngine {

	PhysicsDebugger physicsDebugger;
	uint64_t World::s_EntitiesInWorld;

	World::World()
	{
		s_EntitiesInWorld = 0;
		LKLOG_TRACE("World created");
	}

	World::~World()
	{
		shutdownPhysics();
	}

	void World::onUpdate(float ts)
	{
		m_DynamicWorld->stepSimulation(ts);
		m_DynamicWorld->updateAabbs();
		m_DynamicWorld->computeOverlappingPairs();
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

	bool World::pickBody(glm::vec3& rayFrom, glm::vec3& rayTo)
	{
		if (!m_DynamicWorld)
			return false;

		btVector3 from{ rayFrom.x, rayFrom.y, rayFrom.z };
		btVector3 to{ rayTo.x, rayTo.y, rayTo.z };

		btCollisionWorld::ClosestRayResultCallback rayCallback(from, to);

		rayCallback.m_flags |= btTriangleRaycastCallback::kF_UseGjkConvexCastRaytest; // TODO: Switch the flag to the newly optimized one
		m_DynamicWorld->rayTest(from, to, rayCallback);


		if (rayCallback.hasHit())
		{
			// LKLOG_TRACE("RAY HIT");
			btVector3 pickPos = rayCallback.m_hitPointWorld;
			btRigidBody* body = (btRigidBody*)btRigidBody::upcast(rayCallback.m_collisionObject);
			if (body)
			{
				if (!(body->isStaticObject() || body->isKinematicObject()))
				{
					m_PickedBody = body;
					m_SavedState = m_PickedBody->getActivationState();
					m_PickedBody->setActivationState(DISABLE_DEACTIVATION);
					// LKLOG_CRITICAL("Raycast hit: {0}", body->getUserIndex());
				}
			}

			m_OldPickingPos = to;
			m_HitPos = pickPos;
			m_OldPickingDist = (pickPos - from).length();
		}
		LKLOG_INFO("");
		return false;
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

	bool World::mouseButtonCallback(int button, int state, float x, float y)
	{
		if (state == 1)
		{
			if (button == 0)
			{
				auto cam = m_Scene->getCamera();
				glm::mat4 viewProj = cam->getViewProjection();

				float distance = 200.0f;
				auto [rayFrom, rayTo] = raycast(*cam);
				Renderer::drawLine(rayFrom, rayTo * distance);

				btVector3 from = btVector3(rayFrom.x, rayFrom.y, rayFrom.z);
				btVector3 to = btVector3(rayTo.x, rayTo.y, rayTo.z);
				btCollisionWorld::ClosestRayResultCallback rayCallback(btVector3(rayFrom.x, rayFrom.y, rayFrom.z), btVector3(rayTo.x, rayTo.y, rayTo.z));
				m_DynamicWorld->rayTest(from, to, rayCallback);
				if (rayCallback.hasHit())
				{
					// LKLOG_CRITICAL("HIT");
				}
				else
				{
					// LKLOG_INFO("");
				}
				// pickBody(rayFrom, rayTo);
			}
		}
		else
		{
			if (button == 0 && m_ConstraintsEnabled)
			{
				removePickConstraint();
			}
		}

		return false;
	}

	bool World::mouseMoveCallback(float x, float y)
	{
		if (m_ConstraintsEnabled)
		{
			return false;
		}
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
		auto cam = camera;
		auto screenWidth = cam.getScreenWidth();
		auto screenHeight = cam.getScreenHeight();
		auto projection = cam.getProjection();
		auto view = cam.getView();
		// Lock the ray to the middle of the screen, test for now
		// mouseX = screenWidth / 2;
		// mouseY = screenHeight / 2;

		glm::vec4 rayStart_NDC(
			((float)mouseX/(float)screenWidth  - 0.5f) * 2.0f, // [0,  width] -> [-1,1]
			((float)mouseY/(float)screenHeight - 0.5f) * 2.0f, // [0, height] -> [-1,1]
			-1.0, // The near plane maps to Z=-1
			1.0f
		);
		glm::vec4 rayEnd_NDC(
			((float)mouseX/(float)screenWidth  - 0.5f) * 2.0f,
			((float)mouseY/(float)screenHeight - 0.5f) * 2.0f,
			0.0,
			1.0f
		);

		glm::mat4 invViewProjection = glm::inverse(projection * view);
		glm::vec4 rayStart_world = invViewProjection * rayStart_NDC; rayStart_world/=rayStart_world.w;
		glm::vec4 rayEnd_world   = invViewProjection * rayEnd_NDC  ; rayEnd_world  /=rayEnd_world.w;

		glm::vec3 rayDirection_world(rayEnd_world - rayStart_world);
		rayDirection_world = glm::normalize(rayDirection_world);
		glm::vec3 rayPos(rayStart_world);
		glm::vec3 rayDir(glm::normalize(rayDirection_world));

		return { rayPos, rayDir };
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
					LKLOG_WARN("SOFTBODY CREATED");
				}
			}
		}
	}

	glm::vec3 World::convertWorldToNDC(const btVector3& worldCoords, float screenWidth, float screenHeight)
	{
		// Convert world space coordinates to OpenGL clip space coordinates
		glm::vec4 clipCoords = glm::vec4(worldCoords.x(), worldCoords.y(), -worldCoords.z(), 1.0f);
		// Convert from clip space to NDC
		clipCoords /= clipCoords.w;
		// Convert to screen space
		float halfScreenWidth = screenWidth / 2.0f;
		float halfScreenHeight = screenHeight / 2.0f;
		glm::vec3 screenCoords = glm::vec3((clipCoords.x + 1.0f) * halfScreenWidth, (1.0f - clipCoords.y) * halfScreenHeight, clipCoords.z);

		return screenCoords;
	}

	glm::vec3 World::convertNDCToWorld(const glm::vec3& ndcCoords, float screenWidth, float screenHeight, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
	{
		// Convert from screen space to clip space
		float halfScreenWidth = screenWidth / 2.0f;
		float halfScreenHeight = screenHeight / 2.0f;
		glm::vec4 clipCoords = glm::vec4((ndcCoords.x / halfScreenWidth) - 1.0f, 1.0f - (ndcCoords.y / halfScreenHeight), ndcCoords.z, 1.0f);

		// Convert from clip space to eye space
		glm::vec4 eyeCoords = glm::inverse(projectionMatrix) * clipCoords;
		eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);

		// Convert from eye space to world space
		glm::mat4 viewProjectionMatrix = projectionMatrix * viewMatrix;
		glm::mat4 inverseViewProjectionMatrix = glm::inverse(viewProjectionMatrix);
		glm::vec4 worldCoords = inverseViewProjectionMatrix * eyeCoords;
		worldCoords /= worldCoords.w;

		return glm::vec3(worldCoords.x, worldCoords.y, -worldCoords.z);
	}
}
