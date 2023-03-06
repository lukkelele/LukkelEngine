#include "LKpch.h"
#include "LukkelEngine/Physics/Body/RigidBodyFactory.h"
#include "LukkelEngine/Physics/World.h"


namespace LukkelEngine {

	RigidBodyFactory::RigidBodyFactory()
	{
	}


	RigidBody& RigidBodyFactory::createRigidBody(glm::vec3 dimensions, glm::vec3 offset, float mass, RigidBody::Type bodyType,
												float friction, float restitution, glm::vec3 inertia)
	{
		int id = World::s_CurrentWorldObjects;
		btVector3 dims{ dimensions.x, dimensions.y, dimensions.z };
		btVector3 off{ offset.x, offset.y, offset.z };
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(off);
		RigidBody rigidBody;
		rigidBody.m_Inertia = { inertia.x, inertia.y, inertia.z };
		rigidBody.m_Shape = new btBoxShape(dims);
		rigidBody.m_Mass = mass;
		rigidBody.m_MotionState = new MotionState(transform);
		rigidBody.m_MotionState->setWorldTransform(transform);
		rigidBody.m_Shape->calculateLocalInertia(mass, rigidBody.m_Inertia);
		btRigidBody::btRigidBodyConstructionInfo boxBodyConstructionInfo(mass, rigidBody.m_MotionState, rigidBody.m_Shape, rigidBody.m_Inertia);
		rigidBody.m_RigidBody = new btRigidBody(boxBodyConstructionInfo);
		rigidBody.setFriction(friction);
		rigidBody.setRestitution(restitution);
		rigidBody.m_RigidBody->forceActivationState(DISABLE_DEACTIVATION);
		rigidBody.m_RigidBody->setUserPointer((void*)id);
		rigidBody.m_RigidBody->setUserIndex(id);

		switch (bodyType)
		{
			case RigidBody::Type::DYNAMIC:
				rigidBody.setCollisionFlags(btCollisionObject::CF_DYNAMIC_OBJECT);
				rigidBody.setActivationState(DISABLE_DEACTIVATION);
				break;

			case RigidBody::Type::KINEMATIC:
				rigidBody.setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
				rigidBody.setActivationState(DISABLE_DEACTIVATION);
				break;

			case RigidBody::Type::STATIC:
				rigidBody.setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
				rigidBody.setActivationState(DISABLE_DEACTIVATION);
				break;
		}

		return rigidBody;
	}

}
