#include "LKpch.h"
#include "LukkelEngine/Physics/Body/RigidBody.h"


namespace LukkelEngine {


	RigidBody::RigidBody(glm::vec3 dimensions, glm::vec3 offset, float mass,
				  RigidBody::Type bodyType, float friction, float restitution, glm::vec3 inertia)
	{
		btVector3 dims{ dimensions.x, dimensions.y, dimensions.z };
		btVector3 off{ offset.x, offset.y, offset.z };
		m_Dimensions = dims;
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

	std::pair<glm::vec3, glm::quat> RigidBody::getPosAndRotation()
	{		
		btTransform transform = getWorldTransform();
		btVector3 position = transform.getOrigin();
		btQuaternion rotation = transform.getRotation();
		glm::vec3 pos(position.x(), position.y(), position.z());
		glm::mat4 rot = glm::mat4_cast(glm::quat(rotation.getW(), rotation.getX(), rotation.getY(), rotation.getZ()));
		return std::make_pair(pos, rot);
	}
}