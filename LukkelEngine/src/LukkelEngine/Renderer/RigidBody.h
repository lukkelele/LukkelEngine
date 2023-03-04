#pragma once

#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Debug/Debugger.h"

#include "glm/glm.hpp"
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"


namespace LukkelEngine {

	class RigidBody
	{
	public:
		enum class BodyType { STATIC, DYNAMIC };
		BodyType bodyType = BodyType::STATIC;

		RigidBody() = default;
		RigidBody(btVector3& dimensions, btVector3& offset, float mass = 1.0f);

		glm::vec3 getPosition() { return glm::vec3(m_Position.getX(), m_Position.getY(), m_Position.getZ()); }
		glm::mat4 getModelTransform(float ts);
		void getWorldTransform(btScalar* transform);
		btTransform getWorldTransform() { return m_RigidBody->getWorldTransform(); }

		glm::mat4 getRotation(btTransform worldTransform);
		btRigidBody* m_RigidBody = nullptr;

	public:
		btVector3 m_Position{ 0.0f, 0.0f, 0.0f };
		btVector3 m_Dimensions{ 1.0f, 1.0f, 1.0f };
		btCollisionShape* m_Shape = nullptr;
		btDefaultMotionState* m_MotionState = nullptr;

		btScalar m_Mass = 1.0f;
		float m_Friction = 1.0f;
		float m_Restitution = 0.20f;
		glm::vec3 m_Scale{ 1.0f, 1.0f, 1.0f };
		glm::vec3 m_Rotation{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Translation{ 0.0f, 0.0f, 0.0f };

		btVector3 m_Inertia{ 0.0f, 0.0f, 0.0f };
		btVector3 m_LinearVelocity{ 0.0f, 0.0f, 0.0f };
		btVector3 m_AngularVelocity{ 0.0f, 0.0f, 0.0f };
	};

}