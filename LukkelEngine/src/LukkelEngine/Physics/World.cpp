#include "LKpch.h"
#include "LukkelEngine/Physics/World.h"
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Scene/Entity.h"

#include "LukkelEngine/Core/Application.h"


namespace LukkelEngine {

	PhysicsDebugger physicsDebugger;

	World::World()
	{

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
		// Might need to flush shader here because of draw problems
		// m_DynamicWorld->debugDrawWorld(); // BUGGED
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

		physicsDebugger.setDebugMode(btIDebugDraw::DBG_DrawWireframe + btIDebugDraw::DBG_DrawContactPoints);
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
			btVector3 pickPos = rayCallback.m_hitPointWorld;
			btRigidBody* body = (btRigidBody*)btRigidBody::upcast(rayCallback.m_collisionObject);
			if (body)
			{
				if (!(body->isStaticObject() || body->isKinematicObject()))
				{
					LKLOG_CRITICAL("PICKED OBJECT!");
					m_PickedBody = body;
					m_SavedState = m_PickedBody->getActivationState();
					m_PickedBody->setActivationState(DISABLE_DEACTIVATION);

					btVector3 localPivot = body->getCenterOfMassTransform().inverse() * pickPos;
					btPoint2PointConstraint* p2p = new btPoint2PointConstraint(*body, localPivot);
					m_DynamicWorld->addConstraint(p2p, true);
					m_PickedConstraint = p2p;

					btScalar mousePickClamping = 30.f;
					p2p->m_setting.m_impulseClamp = mousePickClamping;
					// Very weak constraint for picking
					p2p->m_setting.m_tau = 0.001f;
				}
			}

			m_OldPickingPos = to;
			m_HitPos = pickPos;
			m_OldPickingDist = (pickPos - from).length();
		}
		return false;
	}

	void World::stepSimulation(float ts)
	{
		m_DynamicWorld->stepSimulation(ts);
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

				float distance = 500.0f;
				auto [rayFrom, rayTo] = raycast(*cam);
				Renderer::drawLine(rayFrom, rayTo * distance);
				btCollisionWorld::ClosestRayResultCallback rayCallback(btVector3(rayFrom.x, rayFrom.y, rayFrom.z), btVector3(rayTo.x, rayTo.y, rayTo.z));
				m_DynamicWorld->rayTest(btVector3(rayFrom.x, rayFrom.y, rayFrom.z), btVector3(rayTo.x, rayTo.y, rayTo.z), rayCallback);

				if (rayCallback.hasHit())
				{
					LKLOG_CRITICAL("Raycast: HIT REGISTERED");
				} 
				else
				{
					LKLOG_INFO("Raycast: NO HIT");
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
		mouseX = screenWidth / 2;
		mouseY = screenHeight / 2;

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

	void World::createPickingConstraint(Mesh& mesh)
	{
		// Get the rigidbody that is to be added a constraint
		btRigidBody* rigidbody = mesh.getRigidBody();
		rigidbody->setActivationState(DISABLE_DEACTIVATION);

		// Create a transform for the pivot point
		btTransform pivot;
		pivot.setIdentity();
	
		// Create our constraint object
		btGeneric6DofConstraint* dof6 = new btGeneric6DofConstraint(*rigidbody, pivot, true);
		bool bLimitAngularMotion = true;
		if (bLimitAngularMotion) {
			dof6->setAngularLowerLimit(btVector3(0,0,0));
			dof6->setAngularUpperLimit(btVector3(0,0,0));
		}
	
		// Add the constraint to the world
		m_DynamicWorld->addConstraint(dof6,true);
		// Store a pointer to the constraint
		m_PickedConstraint = dof6;
	
		// Define the 'strength'
		float cfm = 0.5f;
		dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 0);
		dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 1);
		dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 2);
		dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 3);
		dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 4);
		dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 5);
	
		// Define the 'error reduction'
		float erp = 0.5f;
		dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,0);
		dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,1);
		dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,2);
		dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,3);
		dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,4);
		dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,5);
	
		// Save data for future reference
		// m_oldPickingDist  = (output.hitPoint - m_cameraPosition).length();
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
