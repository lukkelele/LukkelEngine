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
		ConstraintEvent(UUID& id, btTypedConstraint* constraint, ConstraintType constraintType)
			: m_ID(id), m_Constraint(constraint), m_ConstraintType(constraintType) {}

		ConstraintType getConstraintType() const { return m_ConstraintType; }
		btTypedConstraint* getConstraint() const { return m_Constraint; }
		UUID getID() const { return m_ID; }

	protected:
		UUID m_ID;
		btTypedConstraint* m_Constraint = nullptr;
		ConstraintType m_ConstraintType = ConstraintType::Null;
	};


	class ConstraintAddedEvent : public ConstraintEvent
	{
	public:
		ConstraintAddedEvent(UUID& id, btTypedConstraint* constraint, ConstraintType constraintType)
			: ConstraintEvent(id, constraint, constraintType) {}

		EventType getEventType() const { return EventType::ConstraintAdded; }
		const char* getName() const { return "ConstraintAddedEvent"; }
	};

	class ConstraintRemovedEvent : public ConstraintEvent
	{
	public:
		ConstraintRemovedEvent(UUID& id, btTypedConstraint* constraint, ConstraintType constraintType)
			: ConstraintEvent(id, constraint, constraintType) {}

		EventType getEventType() const { return EventType::ConstraintRemoved; }
		const char* getName() const { return "ConstraintRemovedEvent"; }
	};


}
