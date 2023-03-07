#pragma once
#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Physics/Body/MotionState.h"

#include "glm/glm.hpp"
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"


namespace LukkelEngine {

	class RigidBody
	{
	public:
		enum class Type { STATIC, DYNAMIC, KINEMATIC };

		RigidBody() = default;
		~RigidBody() = default;

		void onUpdate(float ts);
		glm::vec3 getPosition() { return glm::vec3(m_Position.getX(), m_Position.getY(), m_Position.getZ()); }
		btTransform getWorldTransform() { return m_RigidBody->getWorldTransform(); }
		btCollisionShape* getCollisionShape() { return m_RigidBody->getCollisionShape(); }
		int getShapeType() { return m_RigidBody->getCollisionShape()->getShapeType(); }

		void setFriction(float f) { m_Friction = f; }
		void setRestitution(float r) { m_Restitution= r; }
		void setWorldTransform(glm::mat4& transform);
		void setCollisionFlags(int flags) { m_RigidBody->setCollisionFlags(flags); }
		void setActivationState(int state) { m_RigidBody->setActivationState(state); }

	private:
		btCollisionShape* m_Shape = nullptr;
		btRigidBody* m_RigidBody = nullptr;
		MotionState* m_MotionState = nullptr;
		Type m_Type = Type::STATIC;

		btVector3 m_Position{ 0.0f, 0.0f, 0.0f };
		btVector3 m_Dimensions{ 1.0f, 1.0f, 1.0f };
		btVector3 m_Inertia{ 0.0f, 0.0f, 0.0f };
		btVector3 m_LinearVelocity{ 0.0f, 0.0f, 0.0f };
		btVector3 m_AngularVelocity{ 0.0f, 0.0f, 0.0f };

		float m_Mass = 1.0f;
		float m_Friction = 1.0f;
		float m_Restitution = 0.20f;

		friend class RigidBodyFactory;
	};

}