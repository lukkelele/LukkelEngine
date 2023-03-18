#pragma once
#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Physics/Body/MotionState.h"
#include "LukkelEngine/Event/RigidBodyEvent.h"

#include <glm/glm.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>


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
		glm::vec3 getPosition() { return glm::vec3(m_Position.getX(), m_Position.getY(), m_Position.getZ()); }
		glm::vec3 getDimensions() { return glm::vec3(m_Dimensions.getX(), m_Dimensions.getY(), m_Dimensions.getZ()); }
		glm::vec3 getLinearVelocity() const { return glm::vec3(m_LinearVelocity.x(), m_LinearVelocity.y(), m_LinearVelocity.z()); }
		void setLinearVelocity(glm::vec3& linearVelocity);
		int getShapeType() { return m_RigidBody->getCollisionShape()->getShapeType(); }
		std::pair<glm::vec3, glm::quat> getPosAndRotation();

		btTransform getWorldTransform();
		btRigidBody* getRigidBody() { return m_RigidBody; }
		btCollisionShape* getCollisionShape() { return m_RigidBody->getCollisionShape(); }
		RigidBody::Type getType() const { return m_Type; }

		void moveBody(glm::vec3 translation);

		// Create template for adding constraints
		void addPivotConstraint(glm::vec3 pivot);

		void setFriction(float f) { m_Friction = f; }
		void setRestitution(float r) { m_Restitution= r; }
		void setWorldTransform(glm::mat4& transform);
		void setCollisionFlags(int flags) { m_RigidBody->setCollisionFlags(flags); }
		void setActivationState(int state) { m_RigidBody->setActivationState(state); }

		btVector3 m_Position{ 0.0f, 0.0f, 0.0f };
		btVector3 m_Dimensions{ 1.0f, 1.0f, 1.0f };
		btVector3 m_Inertia{ 0.0f, 0.0f, 0.0f };
		btVector3 m_LinearVelocity{ 0.0f, 0.0f, 0.0f };
		btVector3 m_AngularVelocity{ 0.0f, 0.0f, 0.0f };

		const uint64_t getID() const { return m_ID; }
		void setID(uint64_t ID) { m_ID = ID; }
		bool isAltered = false;

	private:
		btCollisionShape* m_Shape = nullptr;
		btRigidBody* m_RigidBody = nullptr;
		MotionState* m_MotionState = nullptr;
		Type m_Type = Type::STATIC;
		uint64_t m_ID;

		float m_Mass = 1.0f;
		float m_Friction = 1.0f;
		float m_Restitution = 0.20f;

		friend class RigidBodyFactory;
		friend class World;
	};

}