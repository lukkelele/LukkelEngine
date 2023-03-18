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
		rigidBody.setCollisionFlags(bodyType);
		return rigidBody;
	}

	RigidBody RigidBodyFactory::createRigidBody(UUID id, glm::vec3 dimensions, glm::vec3 offset, float mass, RigidBody::Type bodyType,
												float friction, float restitution, glm::vec3 inertia)
	{
		RigidBody rigidBody(dimensions, offset, mass, bodyType, friction, restitution, inertia);
		rigidBody.setID(id);
		rigidBody.m_RigidBody->setUserIndex(id);
		rigidBody.m_RigidBody->setUserPointer((void*)((uint64_t)id));
		LKLOG_INFO("RigidBody ID: {0}", id);
		rigidBody.setCollisionFlags(bodyType);
		return rigidBody;
	}

	void RigidBodyFactory::addPivotConstraint(RigidBody& rigidbody, btVector3 pivot)
	{
		btTypedConstraint* p2p = new btPoint2PointConstraint(*rigidbody.getRigidBody(), pivot);
	}

}
