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
		float m[16];
		float glMat[16];
		btTransform tr;
		btMatrix3x3 rot;
		
		btDefaultMotionState* motionState = (btDefaultMotionState*)m_RigidBody->getMotionState();
		motionState->m_graphicsWorldTrans.getOpenGLMatrix(glMat);
		glm::mat4 model = glm::make_mat4(glMat);
		return model;
	}

	void RigidBody::getWorldTransform(btScalar* transform)
	{
		btTransform t;
		btDefaultMotionState* motionState = (btDefaultMotionState*)m_RigidBody->getMotionState();
		if (motionState)
		{
			motionState->getWorldTransform(t);
			t.getOpenGLMatrix(transform);
		}
	}

	glm::mat4 RigidBody::getRotation(btTransform worldTransform)
	{
		btQuaternion rot = worldTransform.getRotation();
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), rot.getAngle(),
			glm::vec3(rot.getAxis().getX(), rot.getAxis().getY(), rot.getAxis().getZ()));
		return rotation;
	}

			
}