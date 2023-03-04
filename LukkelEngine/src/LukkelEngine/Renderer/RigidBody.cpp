#include "LKpch.h"
#include "LukkelEngine/Renderer/RigidBody.h"


namespace LukkelEngine {

	RigidBody::RigidBody(btVector3& dimensions, btVector3& offset, float mass)
			: m_Dimensions(dimensions), m_Mass(mass)
	{
		m_Shape = new btBoxShape(dimensions);
		m_MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), offset));
		m_Shape->calculateLocalInertia(m_Mass, m_Inertia);
		btRigidBody::btRigidBodyConstructionInfo boxBodyConstructionInfo(mass, m_MotionState, m_Shape, m_Inertia);
		m_RigidBody = new btRigidBody(boxBodyConstructionInfo);
		m_RigidBody->setFriction(m_Friction);
		m_RigidBody->setRestitution(m_Restitution);
		m_RigidBody->forceActivationState(DISABLE_DEACTIVATION);
	}

	glm::mat4 RigidBody::getModelTransform(float ts)
	{
		btTransform translation;
		btTransform worldTransform = m_RigidBody->getWorldTransform();
		// worldTransform.setOrigin(m_Position);

		// m_Position = worldTransform.getOrigin();
		btTransformUtil::integrateTransform(worldTransform, m_LinearVelocity, m_AngularVelocity, ts, translation);
		m_RigidBody->getMotionState()->setWorldTransform(translation);

		btVector3 t = translation.getOrigin();
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(t.getX(), t.getY(), t.getZ()));

		// // Debugger::printVec3(t, "TRANSLATION");
		glm::mat4 rotationMatrix = getRotation(translation);
		// glm::mat4 translationMatrix(1.0f);
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), m_Scale);
		glm::mat4 modelTransform = translationMatrix * rotationMatrix * scaleMatrix;

		return modelTransform;
	}

	glm::mat4 RigidBody::getRotation(btTransform worldTransform)
	{
		btQuaternion rot = worldTransform.getRotation();
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), rot.getAngle(),
			glm::vec3(rot.getAxis().getX(), rot.getAxis().getY(), rot.getAxis().getZ()));
		return rotation;
	}

			
}