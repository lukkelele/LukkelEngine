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
		enum Type
		{ 
			STATIC = btCollisionObject::CF_STATIC_OBJECT,
			DYNAMIC = btCollisionObject::CF_DYNAMIC_OBJECT,
			KINEMATIC = btCollisionObject::CF_KINEMATIC_OBJECT
		};

		RigidBody() = default;
		RigidBody(glm::vec3 dimensions, glm::vec3 offset, float mass, RigidBody::Type bodyType, 
				  float friction, float restitution, glm::vec3 inertia);
		RigidBody(const RigidBody& other) = default;
		~RigidBody() = default;

		void onUpdate(float ts);
		btTransform getWorldTransform();
		glm::vec3 getPosition() { return glm::vec3(m_Position.getX(), m_Position.getY(), m_Position.getZ()); }
		btRigidBody* getRigidBody() { return m_RigidBody; }
		btCollisionShape* getCollisionShape() { return m_RigidBody->getCollisionShape(); }
		int getShapeType() { return m_RigidBody->getCollisionShape()->getShapeType(); }
		RigidBody::Type getType() const { return m_Type; }
		glm::vec3 getDimensions() { return glm::vec3(m_Dimensions.getX(), m_Dimensions.getY(), m_Dimensions.getZ()); }

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
		friend class World;
	};

}