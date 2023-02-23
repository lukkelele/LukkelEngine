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
#define LK_WORLD_GRAVITY_SLOWER btVector3(0.0f, -1.5f, 0.0f)
#define LK_WORLD_GRAVITY_SLOWEST btVector3(0.0f, -0.5f, 0.0f)
#define LK_WORLD_GRAVITY_FAST btVector3(0.0f, -18.0f, 0.0f)


namespace LukkelEngine {
	
	class WorldPhysics
	{
	public:
		btRigidBody* createGround(btVector3 dimensions = { 5.0f, 1.0f, 5.0f }, btVector3 position = { 0.0f, -4.0f, 0.0f });
	};
}