#include "LKpch.h"
#include "LukkelEngine/Physics/World.h"
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Scene/Entity.h"

namespace LukkelEngine {

	GLDebugDrawer debugDrawer;

	World::World()
	{
	}

	World::~World()
	{
		shutdownPhysics();
	}

	void World::onUpdate(float ts)
	{
		m_World->stepSimulation(ts);
		m_World->updateAabbs();
		m_World->computeOverlappingPairs();

		// testCastRays();
		// m_World->debugDrawWorld();
	}

	void World::initPhysics(Scene* scene)
	{
		m_Scene = scene;
		btBroadphaseInterface* broadphase = new btDbvtBroadphase();
		btDefaultCollisionConfiguration* collisionConfig = new btDefaultCollisionConfiguration();
		btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfig);
		btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

		m_World = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);
		m_World->setGravity(LK_WORLD_GRAVITY_SLOW);
		debugDrawer.setDebugMode(btIDebugDraw::DBG_MAX_DEBUG_DRAW_MODE);
		// debugDrawer.setDebugMode(btIDebugDraw::DBG_DrawWireframe);
		m_World->setDebugDrawer(&debugDrawer);
	}

	void World::shutdownPhysics()
	{
		delete m_World;
		delete m_Broadphase;
		delete m_CollisionConfig;
		delete m_Dispatcher;
		delete m_Solver;
	}

	btVector3 World::shootRay(uint16_t x, uint16_t y, btVector3 pos, btVector3 target)
	{
		float tanFov = 1.0f / m_NearPlane;
		float fov = btScalar(2.0) * btAtan(tanFov);
		btVector3 up{ 0, 1, 0 };
		btVector3 rayFrom = pos;
		btVector3 rayForward = (target - pos);
		rayForward.normalize();
		rayForward *= m_FarPlane;
	
		// Find the horizontal and vertical vectors relative to the current camera view
		btVector3 ver = up;
		btVector3 hor = rayForward.cross(ver);
		hor.normalize();
		ver = hor.cross(rayForward);
		ver.normalize();
		hor *= 2.0f * m_FarPlane * tanFov;
		ver *= 2.0f * m_FarPlane * tanFov;
		// calculate the aspect ratio
		btScalar aspect = m_ViewportWidth / (btScalar)m_ViewportHeight;
		// adjust the forward-ray based on the X/Y coordinates that were clicked
		hor *= aspect;
		btVector3 rayToCenter = rayFrom + rayForward;
		btVector3 dHor = hor *  1.0f/float(m_ViewportWidth);
		btVector3 dVert = ver * 1.0f/float(m_ViewportHeight);
		btVector3 rayTo = rayToCenter - 0.5f * hor + 0.5f * ver;
		rayTo += btScalar(x) * dHor;
		rayTo -= btScalar(y) * dVert;

		return rayTo;
	}

	bool World::raycast(RaycastResult& raycastResult, btVector3 pos, btVector3 direction)
	{
		auto mousePos = Mouse::getMousePosition();
		float distance = 100.0f;
		btVector3 red(1, 0, 0);
		btVector3 blue(0, 1, 0);
	
		auto cam = m_Scene->m_Camera;
		btVector3 from = pos;
		btVector3 to = direction * distance;

		// Debugger::printVec3(pos, "Camera pos");
		m_World->getDebugDrawer()->drawLine(from, to, btVector4(1, 0, 1, 1));

		btCollisionWorld::ClosestRayResultCallback closestResults(from, to);
		closestResults.m_flags |= btTriangleRaycastCallback::kF_FilterBackfaces;
		m_World->rayTest(from, to, closestResults);

		if (closestResults.hasHit())
		{
			// LKLOG_CRITICAL("HITREG");
			btRigidBody* rigidbody = (btRigidBody*)btRigidBody::upcast(closestResults.m_collisionObject);
			if (!rigidbody)
				return false;
			if (rigidbody->isStaticObject() || rigidbody->isKinematicObject())
				return false;

			btVector3 p = from.lerp(to, closestResults.m_closestHitFraction);
			m_World->getDebugDrawer()->drawSphere(p, 6.0f, blue);
			m_World->getDebugDrawer()->drawLine(p, p + closestResults.m_hitNormalWorld, blue);
			raycastResult.body = rigidbody;
			return true;
		}
		return false;
	}

	/**
	 * @brief Demo code for raycasts in Bullet3
	*/
	void World::testCastRays()
	{
		bool firstHit = true;
		bool allHits = false;
		static float up = 0.0f;
		static float dir = 1.0f;

		{
			up += 0.005 * dir;
			if (btFabs(up) > 1.0f)
			{
				dir *= -1.0f;
			}
			static float angle = 0.f;
			angle += 0.01f;

			// btTransform tr = m_World->getCollisionObjectArray()[1]->getWorldTransform();
			// m_World->getCollisionObjectArray()[1]->setWorldTransform(tr);
			
			// Make all cubes rotate and not just the first one
			entt::basic_view meshes = m_Scene->m_Registry.view<RigidBodyComponent>();
			for (entt::entity e : meshes)
			{
				// tr.setRotation(btQuaternion(btVector3(0, 1, 0), angle));
				Entity entity = { e, m_Scene };
				RigidBodyComponent& body = entity.getComponent<RigidBodyComponent>();
				btTransform t = body.rigidBody->getWorldTransform();
				t.setRotation(btQuaternion(btVector3(0, 1, 0), angle));

				if (body.bodyType != RigidBodyComponent::BodyType::STATIC)
				{
					body.rigidBody->setWorldTransform(t);
				}
			}
		}

		// Step the simulation
		if (m_World)
		{
			btVector3 red(1, 0, 0);
			btVector3 blue(0, 0, 1);

			// All hits
			if (allHits)
			{
				btVector3 from = Vector3::btVec3(m_Scene->m_Camera->getPosition());
				btVector3 to = Vector3::btVec3(m_Scene->m_Camera->m_ForwardDir) * 1.0f; // times distance
				m_World->getDebugDrawer()->drawLine(from, to, btVector4(0, 1, 0, 1));
				btCollisionWorld::AllHitsRayResultCallback allResults(from, to);

				allResults.m_flags |= btTriangleRaycastCallback::kF_KeepUnflippedNormal;
				allResults.m_flags |= btTriangleRaycastCallback::kF_UseSubSimplexConvexCastRaytest;
				m_World->rayTest(from, to, allResults);

				for (int i = 0; i < allResults.m_hitFractions.size(); i++)
				{
					LKLOG_INFO("Registered hit: {0}", i + 1);
					btVector3 p = from.lerp(to, allResults.m_hitFractions[i]);
					m_World->getDebugDrawer()->drawSphere(p, 5.0f, red);
					m_World->getDebugDrawer()->drawLine(p, p + allResults.m_hitNormalWorld[i], red);
				}
			}

			// First hit
			if (firstHit)
			{
				btVector3 from = Vector3::btVec3(m_Scene->m_Camera->getPosition());
				btVector3 to = Vector3::btVec3(m_Scene->m_Camera->m_ForwardDir) * 50.0f; // times distance
				// btVector3 from(-30, 1.2, 0);
				// btVector3 to(30, 1.2, 0);
				m_World->getDebugDrawer()->drawLine(from, to, btVector4(0, 0, 1, 1));

				btCollisionWorld::ClosestRayResultCallback closestResults(from, to);
				closestResults.m_flags |= btTriangleRaycastCallback::kF_FilterBackfaces;
				m_World->rayTest(from, to, closestResults);

				if (closestResults.hasHit())
				{
					LKLOG_CRITICAL("HITREG");
					btVector3 p = from.lerp(to, closestResults.m_closestHitFraction);
					m_World->getDebugDrawer()->drawSphere(p, 6.0f, blue);
					m_World->getDebugDrawer()->drawLine(p, p + closestResults.m_hitNormalWorld, blue);
				}

			}

		}

	}


}
