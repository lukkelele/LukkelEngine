#include "LKpch.h"
#include "LukkelEngine/Physics/Body/RigidBodyFactory.h"
#include "LukkelEngine/Physics/World.h"


namespace LukkelEngine {

	RigidBodyFactory::RigidBodyFactory()
	{
	}

	RigidBody RigidBodyFactory::createRigidBody(glm::vec3 dimensions, glm::vec3 offset, float mass, RigidBody::Type bodyType,
												float friction, float restitution, glm::vec3 inertia)
	{
		int id = World::s_EntitiesInWorld;
		RigidBody rigidBody(dimensions, offset, mass, bodyType, friction, restitution, inertia);
		// rigidBody.m_RigidBody->setUserPointer((void*)id);
		// rigidBody.m_RigidBody->setUserIndex(id);

		return rigidBody;
	}

}
