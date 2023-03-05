#include "LKpch.h"
#include "LukkelEngine/Renderer/RigidBody.h"


namespace LukkelEngine {

	RigidBody::RigidBody(btVector3& dimensions, btVector3& offset, float mass, Type bodyType)
		: m_Dimensions(dimensions), m_Mass(mass), m_Type(bodyType)
	{
		m_Shape = new btBoxShape(dimensions);
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(offset);
		m_MotionState = new MotionState(transform);
		m_MotionState->setWorldTransform(transform);
		m_Shape->calculateLocalInertia(m_Mass, m_Inertia);
		btRigidBody::btRigidBodyConstructionInfo boxBodyConstructionInfo(mass, m_MotionState, m_Shape, m_Inertia);
		m_RigidBody = new btRigidBody(boxBodyConstructionInfo);
		m_RigidBody->setFriction(m_Friction);
		m_RigidBody->setRestitution(m_Restitution);
		m_RigidBody->forceActivationState(DISABLE_DEACTIVATION);
		// rigidBody->setUserPointer((void*) [INDEXING] ); // TODO
	}

	void RigidBody::onUpdate(float ts)
	{
	}

	glm::mat4 RigidBody::getTransform()
	{
		btTransform transform;
		m_RigidBody->getMotionState()->getWorldTransform(transform);
		btVector3 position = transform.getOrigin();
		btQuaternion rotation = transform.getRotation();

		m_Translation = glm::vec3(position.x(), position.y(), position.z());
		m_Rotation =  glm::mat4_cast(glm::quat(rotation.getW(), rotation.getX(), rotation.getY(), rotation.getZ()));
		// glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(position.x(), position.y(), position.z()));

		return glm::translate(glm::mat4(1.0f), m_Translation)
				* glm::toMat4(m_Rotation)
				* glm::scale(glm::mat4(1.0f), m_Scale);
	}

}