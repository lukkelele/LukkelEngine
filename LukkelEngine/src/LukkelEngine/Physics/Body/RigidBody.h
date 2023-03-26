#pragma once
#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Core/UUID.h"
#include "LukkelEngine/Physics/Body/MotionState.h"

#include <glm/glm.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

namespace LukkelEngine {

	/* Forward declaration */
	class Entity;
	class Constraint;
	enum ConstraintType;

	class Rigidbody
	{
	public:
		enum class Shape 
		{ 
			Cube = 1, 
			Sphere = 2 
		};

		enum Type 
		{ 
			STATIC = btCollisionObject::CF_STATIC_OBJECT,
			DYNAMIC = btCollisionObject::CF_DYNAMIC_OBJECT,
			KINEMATIC = btCollisionObject::CF_KINEMATIC_OBJECT
		};

		Rigidbody() = default;
		Rigidbody(Shape shape, Type bodyType, glm::vec3 dimensions, glm::vec3 offset, float mass, 
				  float friction, float restitution, glm::vec3 inertia);
		Rigidbody(const Rigidbody& other) = default;
		~Rigidbody() = default;

		void OnUpdate(float ts);
		glm::vec3 GetPosition() { return glm::vec3(m_Position.getX(), m_Position.getY(), m_Position.getZ()); }
		glm::vec3 GetDimensions() { return glm::vec3(m_Dimensions.getX(), m_Dimensions.getY(), m_Dimensions.getZ()); }
		glm::vec3 GetLinearVelocity() const { return glm::vec3(m_LinearVelocity.x(), m_LinearVelocity.y(), m_LinearVelocity.z()); }
		void SetLinearVelocity(glm::vec3& linearVelocity);
		int GetShapeType() { return m_Rigidbody->getCollisionShape()->getShapeType(); }
		std::pair<glm::vec3, glm::quat> GetPosAndRotation();

		btTransform GetWorldTransform();
		btRigidBody* GetRigidbody() { return m_Rigidbody; }
		btCollisionShape* GetCollisionShape() { return m_Rigidbody->getCollisionShape(); }
		Rigidbody::Type GetType() const { return m_Type; }

		void MoveBody(glm::vec3 translation);
		// Constraints
		void AddPivotConstraint(glm::vec3 pivot);
		void AddDof6Constraint(glm::vec3 pivot, float cfm = 0.50f, float erp = 0.50f, bool angularMotion = true, bool referenceB = false);
		std::vector<Constraint*> GetConstraints() { return m_Constraints; }

		template<typename T>
		void RemoveConstraint(T constraint);

		void SetFriction(float f) { m_Friction = f; }
		void SetRestitution(float r) { m_Restitution= r; }
		void SetWorldTransform(glm::mat4& transform);
		void SetCollisionFlags(int flags) { m_Rigidbody->setCollisionFlags(flags); }
		void SetActivationState(int state) { m_Rigidbody->setActivationState(state); }

		const UUID GetID() const { return m_ID; }
		void SetID(UUID& ID) { m_ID = ID; }
		void SetUserPointer(Entity* entity) { m_Rigidbody->setUserPointer((void*)(&entity)); }

	private:
		btCollisionShape* m_Shape = nullptr;
		btRigidBody* m_Rigidbody = nullptr;
		std::vector<Constraint*> m_Constraints;
		MotionState* m_MotionState = nullptr;
		Type m_Type = Type::STATIC;
		Shape m_Bodyshape = Shape::Cube;
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