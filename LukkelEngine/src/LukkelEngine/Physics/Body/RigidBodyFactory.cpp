#include "LKpch.h"
#include "LukkelEngine/Physics/Body/RigidbodyFactory.h"
#include "LukkelEngine/Physics/World.h"


namespace LukkelEngine {

	RigidbodyFactory::RigidbodyFactory()
	{
	}

	Rigidbody RigidbodyFactory::createRigidbody(UUID id, Rigidbody::Shape shape, Rigidbody::Type bodyType,
												glm::vec3 dimensions, glm::vec3 offset, float mass,
												float friction, float restitution, glm::vec3 inertia)
	{
		Rigidbody rigidBody(shape, bodyType, dimensions, offset, mass, friction, restitution, inertia);
		rigidBody.setID(id);
		rigidBody.m_Rigidbody->setUserIndex(id);
		// Set up user pointer with the UUID to sync the entity id with the rigid body
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
