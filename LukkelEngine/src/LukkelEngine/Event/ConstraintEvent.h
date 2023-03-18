#pragma once
#include "LukkelEngine/Event/Event.h"
#include "LukkelEngine/Physics/Body/Constraints.h"
#include "LukkelEngine/Core/UUID.h"

#include <glm/glm.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>


namespace LukkelEngine {


	class ConstraintEvent : public Event
	{
	public:
		ConstraintEvent() = default;
		// ConstraintEvent(RigidBody* rigidbody, btTypedConstraint* constraint, ConstraintType constraintType)
		ConstraintEvent(RigidBody* rigidbody, Constraint* constraint)
			: m_RigidBody(rigidbody), m_Constraint(constraint)
		{
			m_ID = m_RigidBody->getID();
		}

		RigidBody& getRigidBody() { return *m_RigidBody; }
		ConstraintType getConstraintType() const { return m_ConstraintType; }
		// btTypedConstraint* getConstraint() { return m_Constraint; }
		Constraint& getConstraint() { return *m_Constraint; }
		UUID getID() const { return m_ID; }

	protected:
		RigidBody* m_RigidBody;
		UUID m_ID;
		// btTypedConstraint* m_Constraint = nullptr;
		ConstraintType m_ConstraintType = ConstraintType::Null;
		Constraint* m_Constraint;
	};


	class ConstraintAddedEvent : public ConstraintEvent
	{
	public:
		// ConstraintAddedEvent(RigidBody& rigidbody, btTypedConstraint* constraint, ConstraintType constraintType)
		ConstraintAddedEvent(RigidBody* rigidbody, Constraint* constraint)
			: ConstraintEvent(rigidbody, constraint) {}

		EventType getEventType() const { return EventType::ConstraintAdded; }
		const char* getName() const { return "ConstraintAddedEvent"; }
	};

	class ConstraintRemovedEvent : public ConstraintEvent
	{
	public:
		ConstraintRemovedEvent(RigidBody* rigidbody, Constraint* constraint)
		{
			m_RigidBody = rigidbody;
			// m_Constraint = constraint->getConstraint();
			m_Constraint = constraint;
			m_ConstraintType = constraint->getConstraintType();
		}

		EventType getEventType() const { return EventType::ConstraintRemoved; }
		const char* getName() const { return "ConstraintRemovedEvent"; }
	};


}
