#include "LKpch.h"
#include "LukkelEngine/Physics/Body/RigidbodyFactory.h"
#include "LukkelEngine/Physics/World.h"


namespace LukkelEngine {

	RigidbodyFactory::RigidbodyFactory()
	{
	}

	Rigidbody RigidbodyFactory::createRigidbody(glm::vec3 dimensions, glm::vec3 offset, float mass, Rigidbody::Type bodyType,
												float friction, float restitution, glm::vec3 inertia)
	{
		int id = World::s_EntitiesInWorld;
		Rigidbody rigidBody(dimensions, offset, mass, bodyType, friction, restitution, inertia);
		rigidBody.setCollisionFlags(bodyType);
		return rigidBody;
	}

	Rigidbody RigidbodyFactory::createRigidbody(UUID id, glm::vec3 dimensions, glm::vec3 offset, float mass, Rigidbody::Type bodyType,
												float friction, float restitution, glm::vec3 inertia)
	{
		Rigidbody rigidBody(dimensions, offset, mass, bodyType, friction, restitution, inertia);
		rigidBody.setID(id);
		rigidBody.m_Rigidbody->setUserIndex(id);
		rigidBody.m_Rigidbody->setUserPointer((void*)((uint64_t)id));
		LKLOG_INFO("Rigidbody ID: {0}", id);
		rigidBody.setCollisionFlags(bodyType);
		return rigidBody;
	}

	void RigidbodyFactory::addPivotConstraint(Rigidbody& rigidbody, btVector3 pivot)
	{
		btTypedConstraint* p2p = new btPoint2PointConstraint(*rigidbody.getRigidbody(), pivot);
	}

}
