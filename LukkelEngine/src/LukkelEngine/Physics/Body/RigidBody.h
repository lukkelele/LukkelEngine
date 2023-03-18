#pragma once
#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Core/UUID.h"
#include "LukkelEngine/Physics/Body/MotionState.h"

#include <glm/glm.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>


namespace LukkelEngine {

	/* Forward declaration */
	class Constraint;
	enum ConstraintType;

	class Rigidbody
	{
	public:
		enum Type
		{ 
			STATIC = btCollisionObject::CF_STATIC_OBJECT,
			DYNAMIC = btCollisionObject::CF_DYNAMIC_OBJECT,
			KINEMATIC = btCollisionObject::CF_KINEMATIC_OBJECT
		};

		Rigidbody() = default;
		Rigidbody(glm::vec3 dimensions, glm::vec3 offset, float mass, Rigidbody::Type bodyType, 
				  float friction, float restitution, glm::vec3 inertia);
		Rigidbody(const Rigidbody& other) = default;
		~Rigidbody() = default;

		void onUpdate(float ts);
		glm::vec3 getPosition() { return glm::vec3(m_Position.getX(), m_Position.getY(), m_Position.getZ()); }
		glm::vec3 getDimensions() { return glm::vec3(m_Dimensions.getX(), m_Dimensions.getY(), m_Dimensions.getZ()); }
		glm::vec3 getLinearVelocity() const { return glm::vec3(m_LinearVelocity.x(), m_LinearVelocity.y(), m_LinearVelocity.z()); }
		void setLinearVelocity(glm::vec3& linearVelocity);
		int getShapeType() { return m_Rigidbody->getCollisionShape()->getShapeType(); }
		std::pair<glm::vec3, glm::quat> getPosAndRotation();

		btTransform getWorldTransform();
		btRigidBody* getRigidbody() { return m_Rigidbody; }
		btCollisionShape* getCollisionShape() { return m_Rigidbody->getCollisionShape(); }
		Rigidbody::Type getType() const { return m_Type; }

		void moveBody(glm::vec3 translation);
		// Constraints
		void addPivotConstraint(glm::vec3 pivot);
		// Current implementation only can remove 1 type at a time
		// void removeConstraint(ConstraintType constraintType);
		std::vector<Constraint*> getConstraints() { return m_Constraints; }

		template<typename T>
		void removeConstraint(T constraint);

		void setFriction(float f) { m_Friction = f; }
		void setRestitution(float r) { m_Restitution= r; }
		void setWorldTransform(glm::mat4& transform);
		void setCollisionFlags(int flags) { m_Rigidbody->setCollisionFlags(flags); }
		void setActivationState(int state) { m_Rigidbody->setActivationState(state); }

		const UUID getID() const { return m_ID; }
		void setID(UUID ID) { m_ID = ID; }
		bool isAltered = false;

	private:
		btCollisionShape* m_Shape = nullptr;
		btRigidBody* m_Rigidbody = nullptr;
		std::vector<Constraint*> m_Constraints;
		MotionState* m_MotionState = nullptr;
		Type m_Type = Type::STATIC;
		UUID m_ID;

		btVector3 m_Position{ 0.0f, 0.0f, 0.0f };
		btVector3 m_Dimensions{ 1.0f, 1.0f, 1.0f };
		btVector3 m_Inertia{ 0.0f, 0.0f, 0.0f };
		btVector3 m_LinearVelocity{ 0.0f, 0.0f, 0.0f };
		btVector3 m_AngularVelocity{ 0.0f, 0.0f, 0.0f };

		float m_Mass = 1.0f;
		float m_Friction = 1.0f;
		float m_Restitution = 0.20f;

		friend class RigidbodyFactory;
		friend class Constraint;
		friend class World;
	};

}