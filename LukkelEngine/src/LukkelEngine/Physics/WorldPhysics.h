#pragma once
/*
	Physics operations for world objects	
*/

#include "LukkelEngine/Core/Base.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

#define LK_WORLD_NEUTRAL 0
#define LK_WORLD_DYNAMIC 1
#define LK_WORLD_GRAVITY_DEFAULT btVector3(0.0f, -9.8f, 0.0f)
#define LK_WORLD_GRAVITY_SLOW btVector3(0.0f, -4.5f, 0.0f)
#define LK_WORLD_GRAVITY_FAST btVector3(0.0f, -18.0f, 0.0f)


namespace LukkelEngine {
	
	class WorldPhysics
	{
	public:
		WorldPhysics(uint8_t worldType = LK_WORLD_DYNAMIC);
		~WorldPhysics() = default;

		void createDynamicWorld();

		btDiscreteDynamicsWorld* m_DynamicWorld; // Set to private
	private:
		// s_ptr<btDiscreteDynamicsWorld> m_DynamicWorld;

		// s_ptr<btBroadphaseInterface> m_Broadphase;
		// s_ptr<btCollisionDispatcher> m_Dispatcher;
		// s_ptr<btDefaultCollisionConfiguration> m_DefaultCollisionConfig;
		// s_ptr<btSequentialImpulseConstraintSolver> m_Solver;
	};
}