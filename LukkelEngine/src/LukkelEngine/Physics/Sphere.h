#pragma once

#include "LukkelEngine/Physics/RigidBody.h"

	// btCollisionShape* sphereShape = new btSphereShape(1.0f);
	// // Set rotation to 0 and set distance on y axis
	// btDefaultMotionState* sphereMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 10.0f, 0)));
	// btScalar mass = 10.0f;
	// btVector3 sphereInertia(0, 0, 0);
	// sphereShape->calculateLocalInertia(mass, sphereInertia);
	// btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(mass, sphereMotionState, sphereShape, sphereInertia);
	// btRigidBody* sphereRigidBody = new btRigidBody(sphereRigidBodyCI);
	// sphereRigidBody->setRestitution(1.0f);
	// sphereRigidBody->setFriction(1.0f);
	// btCollisionShape* groundShape = new btBoxShape(btVector3(4.0f, 1.0f, 4.0f)); // Lenght Height Depth
	// btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -2.0f, 0)));
	// btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0.0f, new btDefaultMotionState(), groundShape, btVector3(0, -10, 0));
	// btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	// groundRigidBody->setFriction(1.0f);
	// groundRigidBody->setRestitution(0.90f);
	// groundRigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);

	// Cube->m_RigidBody = sphereRigidBody;
	// Cube2->m_RigidBody = groundRigidBody;


namespace LukkelEngine {

	namespace CollisionBody {

		class Sphere : public RigidBody
		{
		public:
			Sphere();
			~Sphere() = default;

		};

	}

}