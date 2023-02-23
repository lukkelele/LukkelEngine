#include "LukkelEngine/Physics/WorldPhysics.h"


namespace LukkelEngine {

	// FIXME: Proper way of creating a ground object that is on the heap
	btRigidBody* WorldPhysics::createGround(btVector3 dimensions, btVector3 position)
	{
		btCollisionShape* groundShape = new btBoxShape(position); // Lenght Height Depth
		btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -2.0f, 0)));
		btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0.0f, new btDefaultMotionState(), groundShape, btVector3(0, -10, 0));
		btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
		groundRigidBody->setFriction(1.0f);
		groundRigidBody->setRestitution(0.90f);
		groundRigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
		return groundRigidBody;
	}

}