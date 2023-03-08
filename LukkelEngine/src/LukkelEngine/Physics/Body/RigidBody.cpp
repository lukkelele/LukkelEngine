#include "LKpch.h"
#include "LukkelEngine/Physics/Body/RigidBody.h"


namespace LukkelEngine {


	RigidBody::RigidBody(glm::vec3 dimensions, glm::vec3 offset, float mass,
				  RigidBody::Type bodyType, float friction, float restitution, glm::vec3 inertia)
	{
		btVector3 dims{ dimensions.x, dimensions.y, dimensions.z };
		btVector3 off{ offset.x, offset.y, offset.z };
		m_Shape = new btBoxShape(dims);
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(off);

		m_MotionState = new MotionState(transform);
		m_MotionState->setWorldTransform(transform);
		m_Shape->calculateLocalInertia(m_Mass, m_Inertia);
		btRigidBody::btRigidBodyConstructionInfo boxBodyConstructionInfo(mass, m_MotionState, m_Shape, m_Inertia);

		m_RigidBody = new btRigidBody(boxBodyConstructionInfo);
		m_RigidBody->setFriction(m_Friction);
		m_RigidBody->setRestitution(m_Restitution);
		m_RigidBody->forceActivationState(DISABLE_DEACTIVATION);

		// Does not change collisions, might need to be set AFTER world insertion
		switch (bodyType)
		{
			case RigidBody::Type::DYNAMIC:
				LKLOG_WARN("Setting body: DYNAMIC");
				m_RigidBody->setCollisionFlags(btCollisionObject::CF_DYNAMIC_OBJECT);
				break;
			case RigidBody::Type::KINEMATIC:
				LKLOG_WARN("Setting body: KINEMATIC");
				m_RigidBody->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
				break;
			case RigidBody::Type::STATIC:
				LKLOG_WARN("Setting body: STATIC");
				m_RigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
				break;
		}

	}

	void RigidBody::onUpdate(float ts)
	{
	}

	void RigidBody::setWorldTransform(glm::mat4& transform)
	{
	}

	btTransform RigidBody::getWorldTransform()
	{ 
		if (m_RigidBody)
		{
			return m_RigidBody->getWorldTransform();
		}
		else
			LKLOG_CRITICAL("getWorldTransform() -> rigidbody doesn't exist");
	}
}