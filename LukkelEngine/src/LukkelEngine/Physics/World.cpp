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

		m_DynamicWorld->debugDrawWorld();
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


	btVector3 World::shootRay(uint16_t x, uint16_t y, btVector3 pos, btVector3 target)
	{
		float top = 1.f;
		float bottom = -1.f;
		float nearPlane = 1.f;
		float tanFov = (top - bottom) * 0.5f / nearPlane;
		float fov = btScalar(2.0) * btAtan(tanFov);

		float screenWidth = 1600;
		float screenHeight = 1024;
		btVector3 rayFrom = pos;
		btVector3 rayForward = (target - pos);
		rayForward.normalize();
		float farPlane = 10000.f;
		rayForward *= farPlane;

		btVector3 rightOffset;
		btVector3 cameraUp = btVector3(0, 1, 0);
		btVector3 vertical = cameraUp;
		btVector3 hor;
		hor = rayForward.cross(vertical);
		hor.safeNormalize();
		vertical = hor.cross(rayForward);
		vertical.safeNormalize();

		float tanfov = tanf(0.5f * fov);
		hor *= 2.f * farPlane * tanfov;
		vertical *= 2.f * farPlane * tanfov;

		btScalar aspect;
		float width = float(screenWidth);
		float height = float(screenHeight);

		aspect = width / height;
		hor *= aspect;

		btVector3 rayToCenter = rayFrom + rayForward;
		btVector3 dHor = hor * 1.f / width;
		btVector3 dVert = vertical * 1.f / height;

		btVector3 rayTo = rayToCenter - 0.5f * hor + 0.5f * vertical;
		rayTo += btScalar(x) * dHor;
		rayTo -= btScalar(y) * dVert;
		return rayTo;
	}

	bool World::raycast(RaycastResult& raycastResult, btVector3 pos, btVector3 direction)
	{
		return false;
	}

	std::pair<glm::vec3, glm::vec3> World::castRay(FpsCamera& camera, float mx, float my)
	{
		glm::vec4 mouseClipPos = { mx, my, -1.0f, 1.0f };

		auto inverseProj = glm::inverse(camera.getProjection());
		auto inverseView = glm::inverse(glm::mat3(camera.getView()));

		glm::vec4 ray = inverseProj * mouseClipPos;
		glm::vec3 rayPos = camera.getPosition();
		glm::vec3 rayDir = inverseView * glm::vec3(ray);
		
		return { rayPos, rayDir };
	}


	bool World::pickBody(btVector3& rayFrom, btVector3& rayTo)
	{
		if (!m_DynamicWorld)
			return false;

		btCollisionWorld::ClosestRayResultCallback rayCallback(rayFrom, rayTo);

		rayCallback.m_flags |= btTriangleRaycastCallback::kF_UseGjkConvexCastRaytest; // TODO: Switch the flag to the newly optimized one
		m_DynamicWorld->rayTest(rayFrom, rayTo, rayCallback);

		if (rayCallback.hasHit())
		{
			btVector3 pickPos = rayCallback.m_hitPointWorld;
			btRigidBody* body = (btRigidBody*)btRigidBody::upcast(rayCallback.m_collisionObject);
			if (body)
			{
				//other exclusions?
				if (!(body->isStaticObject() || body->isKinematicObject()))
				{
					m_pickedBody = body;
					m_savedState = m_pickedBody->getActivationState();
					m_pickedBody->setActivationState(DISABLE_DEACTIVATION);
					//printf("pickPos=%f,%f,%f\n",pickPos.getX(),pickPos.getY(),pickPos.getZ());
					btVector3 localPivot = body->getCenterOfMassTransform().inverse() * pickPos;
					btPoint2PointConstraint* p2p = new btPoint2PointConstraint(*body, localPivot);
					m_DynamicWorld->addConstraint(p2p, true);
					m_pickedConstraint = p2p;
					btScalar mousePickClamping = 30.f;
					p2p->m_setting.m_impulseClamp = mousePickClamping;
					//very weak constraint for picking
					p2p->m_setting.m_tau = 0.001f;
				}
			}

			//					pickObject(pickPos, rayCallback.m_collisionObject);
			m_oldPickingPos = rayTo;
			m_hitPos = pickPos;
			m_oldPickingDist = (pickPos - rayFrom).length();
		}
		return false;
	}

	void World::stepSimulation(float ts)
	{
		m_DynamicWorld->stepSimulation(ts);
	}


	void World::removePickConstraint()
	{
		if (m_pickedConstraint)
		{
			m_pickedBody->forceActivationState(m_savedState);
			m_pickedBody->activate();
			m_DynamicWorld->removeConstraint(m_pickedConstraint);
			delete m_pickedConstraint;
			m_pickedConstraint = 0;
			m_pickedBody = 0;
		}
	}

	bool World::mouseButtonCallback(int button, int state, float x, float y)
	{
		if (state == 1)
		{
			if (button == 0 && m_ConstraintsEnabled)
			{
				auto cam = m_Scene->getCamera();
				auto camPos = cam->getPosition();
				auto dir = cam->getDirection();
				btVector3 from{ camPos.x, camPos.y, camPos.z };
				btVector3 rayFrom = from;
				btVector3 to{ dir.x, dir.y, dir.z };
				LKLOG_TRACE("Sending ray");
				btVector3 rayTo = shootRay(x, y, from, to);
	
				LKLOG_WARN("Picking body");
				pickBody(rayFrom, rayTo);
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
			auto cam = m_Scene->getCamera();
			auto camPos = cam->getPosition();
			auto dir = cam->getDirection();
			btVector3 from{ camPos.x, camPos.y, camPos.z };
			btVector3 rayFrom = from;
			btVector3 to{ dir.x, dir.y, dir.z };

			LKLOG_TRACE("Sending ray");
			btVector3 rayTo = shootRay(x, y, from, to);

			LKLOG_TRACE("Checking if to move body");
			movePickedBody(rayFrom, rayTo);

			return false;
		}

		return false;
	}

	bool World::movePickedBody(btVector3& rayFrom, btVector3& rayTo)
	{
		LKLOG_TRACE("pick constraint");
		if (m_pickedBody && m_pickedConstraint)
		{
			LKLOG_TRACE("getting picked constraint");
			try {
				btPoint2PointConstraint* pickCon = static_cast<btPoint2PointConstraint*>(m_pickedConstraint);
				LKLOG_WARN("Got picked constraint");
				if (pickCon)
				{
					// Keep it at the same picking distance
					btVector3 newPivotB;

					btVector3 dir = rayTo - rayFrom;
					dir.normalize();
					dir *= m_oldPickingDist;

					newPivotB = rayFrom + dir;
					pickCon->setPivotB(newPivotB);
					return true;
				}
			} catch (const std::exception& e) {
				LKLOG_CRITICAL("[ERROR] {0}", e.what());
				return false;
			}
		}
		return false;
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


}
