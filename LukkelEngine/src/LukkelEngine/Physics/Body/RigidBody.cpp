#include "LKpch.h"
#include "LukkelEngine/Physics/Body/Rigidbody.h"
#include "LukkelEngine/Physics/World.h"
#include "LukkelEngine/Physics/Body/Constraints.h"
#include "LukkelEngine/Event/ConstraintEvent.h"
#include "LukkelEngine/Scene/Entity.h"

namespace LukkelEngine {

	Rigidbody::Rigidbody(Rigidbody::Shape shape, Rigidbody::Type bodyType, 
						 glm::vec3 dimensions, glm::vec3 offset, float mass,
						 float friction, float restitution, glm::vec3 inertia)
	{
		btVector3 dims{ dimensions.x, dimensions.y, dimensions.z };
		btVector3 off{ offset.x, offset.y, offset.z };
		m_Type = bodyType;
		m_Dimensions = dims;
		m_Shape = new btBoxShape(dims);
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(off);

		m_MotionState = new MotionState(transform);
		m_MotionState->setWorldTransform(transform);
		m_Shape->calculateLocalInertia(m_Mass, m_Inertia);
		btRigidBody::btRigidBodyConstructionInfo boxBodyConstructionInfo(mass, m_MotionState, m_Shape, m_Inertia);

		m_Rigidbody = new btRigidBody(boxBodyConstructionInfo);
		m_Rigidbody->setFriction(m_Friction);
		m_Rigidbody->setRestitution(m_Restitution);
		m_Rigidbody->forceActivationState(DISABLE_DEACTIVATION);
	}

	void Rigidbody::onUpdate(float ts)
	{
	}

	void Rigidbody::moveBody(glm::vec3 translation)
	{
		m_Position = {translation.x, translation.y, translation.z};
		btTransform transform;
		btMotionState* motionState = m_Rigidbody->getMotionState();
		motionState->getWorldTransform(transform);
		transform.setOrigin(m_Position);
		motionState->setWorldTransform(transform);
		m_Rigidbody->setCenterOfMassTransform(transform);
	}

	void Rigidbody::setLinearVelocity(glm::vec3& linearVelocity)
	{
		m_LinearVelocity = { linearVelocity.x, linearVelocity.y, linearVelocity.z };
		m_Rigidbody->setLinearVelocity(m_LinearVelocity);
	}

	void Rigidbody::setWorldTransform(glm::mat4& transform)
	{
	}

	btTransform Rigidbody::getWorldTransform()
	{ 
		if (m_Rigidbody)
		{
			return m_Rigidbody->getWorldTransform();
		}
		else
		{
			LKLOG_CRITICAL("getWorldTransform() -> rigidbody doesn't exist");
		}
	}

	std::pair<glm::vec3, glm::quat> Rigidbody::getPosAndRotation()
	{		
		btTransform transform = getWorldTransform();
		btVector3 position = transform.getOrigin();
		btQuaternion rotation = transform.getRotation();
		glm::vec3 pos(position.x(), position.y(), position.z());
		glm::mat4 rot = glm::mat4_cast(glm::quat(rotation.getW(), rotation.getX(), rotation.getY(), rotation.getZ()));
		return std::make_pair(pos, rot);
	}

	void Rigidbody::addPivotConstraint(glm::vec3 pivot)
	{
		Constraint* constraint = new PivotConstraint(*this, pivot);
		m_Constraints.push_back(constraint);
		LK_WORLD_REGISTER_EVENT(new ConstraintAddedEvent(*constraint));
	}

	void Rigidbody::addDof6Constraint(glm::vec3 pivot, float cfm, float erp, bool angularMotion, bool referenceB)
	{
		Constraint* constraint = new Dof6Constraint(*this, pivot, cfm, erp, angularMotion, referenceB);
		m_Constraints.push_back(constraint);
		LK_WORLD_REGISTER_EVENT(new ConstraintAddedEvent(*constraint));
	}

	template<typename T>
	void Rigidbody::removeConstraint(T constraint)
	{
	}
		template<>
		void Rigidbody::removeConstraint(Constraint* constraint)
		{
			auto it = std::find(m_Constraints.begin(), m_Constraints.end(), constraint);
			LK_WORLD_REGISTER_EVENT(new ConstraintRemovedEvent(*constraint));
			m_Constraints.erase(it);
		}

		template<>
		void Rigidbody::removeConstraint(Constraint::Type type)
		{
			for (auto& constraint : m_Constraints)
			{
				// If the constraint type matches, remove the constraint
				if (constraint->getConstraintType() == type)
				{
					auto it = std::find(m_Constraints.begin(), m_Constraints.end(), constraint);
					LK_WORLD_REGISTER_EVENT(new ConstraintRemovedEvent(*constraint));
					m_Constraints.erase(it);
				}
			}
		}



}