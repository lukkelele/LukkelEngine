#pragma once
#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Debug/Debugger.h"
#include "LukkelEngine/Debug/PhysicsDebugger.h"
#include "LukkelEngine/Scene/Components.h"
#include "LukkelEngine/Renderer/FpsCamera.h"

#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "BulletSoftBody/btSoftBody.h"
#include "bullet3/src/BulletCollision/NarrowPhaseCollision/btRaycastCallback.h"
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "CommonCallbacks.h"

#include "entt/entt.hpp"

#define LK_WORLD_NEUTRAL 0
#define LK_WORLD_DYNAMIC 1
#define LK_WORLD_GRAVITY_DEFAULT btVector3(0.0f, -9.8f, 0.0f)
#define LK_WORLD_GRAVITY_SLOW btVector3(0.0f, -4.5f, 0.0f)
#define LK_WORLD_GRAVITY_SLOWER btVector3(0.0f, -1.5f, 0.0f)
#define LK_WORLD_GRAVITY_SLOWEST btVector3(0.0f, -0.5f, 0.0f)
#define LK_WORLD_GRAVITY_FAST btVector3(0.0f, -18.0f, 0.0f)


namespace LukkelEngine {

	class Scene;

	struct RaycastResult 
	{
		btRigidBody* body;
		btVector3 hitPoint;
	};

	class World
	{
	public:
		World();
		~World();

		void onUpdate(float ts);
		void initPhysics(Scene* scene);
		void shutdownPhysics();

		btVector3 shootRay(uint16_t x, uint16_t y, btVector3 pos, btVector3 target);
		bool raycast(RaycastResult& rayresult, btVector3 pos, btVector3 target);
		std::pair<glm::vec3, glm::vec3> castRay(FpsCamera& cam, float mx, float my);

		void stepSimulation(float ts);
		void addRigidBodyToWorld(btRigidBody* body) { m_DynamicWorld->addRigidBody(body); }
		bool pickBody(btVector3& rayFrom, btVector3& rayTo);

		void addConstraint(btTypedConstraint* constraint, btRigidBody* body);
		void createPickingConstraint(float x, float y);
		void createPickingConstraint(Mesh& mesh);
		void removePickConstraint();

		bool mouseButtonCallback(int button, int state, float x, float y);
		bool mouseMoveCallback(float x, float y);
		bool movePickedBody(btVector3& rayFrom, btVector3& rayTo);

		void createCollisionObject(btCollisionObject* body);

		class btRigidBody* m_pickedBody;
		class btTypedConstraint* m_pickedConstraint;
		int m_savedState;
		btVector3 m_oldPickingPos;
		btVector3 m_hitPos;
		btScalar m_oldPickingDist;

		std::vector<btTypedConstraint*> constraints;
		btTypedConstraint* m_PickedConstraint;

	private:
		btDiscreteDynamicsWorld* m_DynamicWorld = nullptr;
		btBroadphaseInterface* m_Broadphase = nullptr;
		btDefaultCollisionConfiguration* m_CollisionConfig = nullptr;
		btCollisionDispatcher* m_Dispatcher = nullptr;
		btSequentialImpulseConstraintSolver* m_Solver = nullptr;

		b3MouseButtonCallback m_PrevMouseButtonCallback = 0;
		b3MouseMoveCallback m_PrevMouseMoveCallback = 0;
	
		bool m_ConstraintsEnabled = false;

		// TODO: Implement an application function to set this automatically and even without 
		//		 them as members here. Should change on resize events
		float m_ViewportWidth = 1600;
		float m_ViewportHeight = 1024;
		float m_AspectRatio = float(1600.0f/1024.0f);

		// FIXME: BELONGS TO CAMERA, ONLY TEMPORARY
		float m_FOV = 50.0f, m_NearPlane = 0.10f, m_FarPlane = 1000.0f;
		float m_TravelSpeed = 0.10f;
		float m_Distance = 0.50f;

		friend class Scene;
		Scene* m_Scene;
	};
}
