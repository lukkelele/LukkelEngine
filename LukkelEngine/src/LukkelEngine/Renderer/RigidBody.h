#pragma once

#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Debug/Debugger.h"
#include "LukkelEngine/Physics/MotionState.h"


#include "glm/glm.hpp"
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"


namespace LukkelEngine {

	class RigidBody
	{
	public:
		enum class Type { STATIC, DYNAMIC, KINEMATIC };

		RigidBody() = default;
		RigidBody(btVector3& dimensions, btVector3& offset, float mass = 1.0f, Type bodyType = Type::DYNAMIC);

		void onUpdate(float ts);
		void move(float speed);

		glm::vec3 getPosition() { return glm::vec3(m_Position.getX(), m_Position.getY(), m_Position.getZ()); }
		btRigidBody* getRigidBody() { return m_RigidBody; }
		int getShapeType() { return m_RigidBody->getCollisionShape()->getShapeType(); }

		glm::mat4 getTransform();
		btTransform getWorldTransform() { return m_RigidBody->getWorldTransform(); }

	public:
		btVector3 m_Position{ 0.0f, 0.0f, 0.0f };
		btVector3 m_Dimensions{ 1.0f, 1.0f, 1.0f };
		btCollisionShape* m_Shape = nullptr;
		btRigidBody* m_RigidBody = nullptr;
		MotionState* m_MotionState = nullptr;
		Type m_Type = Type::STATIC;

		btScalar m_Mass = 1.0f;
		float m_Friction = 1.0f;
		float m_Restitution = 0.20f;
		glm::vec3 m_Translation{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Scale{ 1.0f, 1.0f, 1.0f };
		glm::quat m_Rotation{ 1.0f, 0.0f, 0.0f, 0.0f };

		btVector3 m_Inertia{ 0.0f, 0.0f, 0.0f };
		btVector3 m_LinearVelocity{ 0.0f, 0.0f, 0.0f };
		btVector3 m_AngularVelocity{ 0.0f, 0.0f, 0.0f };
	};

}