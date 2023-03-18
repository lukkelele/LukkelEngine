#pragma once
#include "LukkelEngine/Event/Event.h"

#include <glm/glm.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>


namespace LukkelEngine {

	enum ConstraintType
	{
		Null      = -1,
		Generic   =  0,
		Pivot     =  1,
		Slider    =  2,
		Spherical =  3,
		Hinge     =  4,
		ConeTwist =  5
	};

	class RigidBodyEvent : public Event
	{
	public:
		ConstraintType getConstraintType() const { return m_ConstraintType; }
		btTypedConstraint* getConstraint() const { return m_Constraint; }

	protected:
		btTypedConstraint* m_Constraint = nullptr;
		ConstraintType m_ConstraintType = ConstraintType::Null;
	};

	class ConstraintAddedEvent : public RigidBodyEvent
	{
	public:
		ConstraintAddedEvent(btTypedConstraint* constraint, ConstraintType constraintType)	
		{
			m_Constraint = constraint;
			m_ConstraintType = constraintType;
		}

		EventType getEventType() const { return EventType::ConstraintAdded; }
		const char* getName() const { return "ConstraintAddedEvent"; }
	};

	class ConstraintRemovedEvent : public RigidBodyEvent
	{
	public:
		EventType getEventType() { return EventType::ConstraintRemoved; }
		const char* getName() { return "ConstraintRemovedEvent"; }
	};


}