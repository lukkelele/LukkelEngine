#include "LukkelEngine/Physics/WorldPhysics.h"


namespace LukkelEngine {


	WorldPhysics::WorldPhysics(uint8_t worldType)
	{
		if (worldType == LK_WORLD_DYNAMIC)
			createDynamicWorld();
	}

	/**
	 * @brief Create new dynamic world
	*/
	void WorldPhysics::createDynamicWorld()
	{
		btBroadphaseInterface* broadphase = new btDbvtBroadphase();
		btDefaultCollisionConfiguration* collisionConfig = new btDefaultCollisionConfiguration();
		btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfig);
		btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

		m_DynamicWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);
		// Gravity set to -9.8 m^2/2
		m_DynamicWorld->setGravity(LK_WORLD_GRAVITY_DEFAULT);
	}

}