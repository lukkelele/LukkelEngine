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
		ConstraintEvent(Constraint& constraint)
			:  m_Constraint(constraint)
		{
			m_ID = constraint.getID();
			m_ConstraintType = constraint.getConstraintType();
		}

		Constraint& getConstraint() { return m_Constraint; }
		ConstraintType getConstraintType() const { return m_ConstraintType; }
		UUID getID() const { return m_ID; }

	protected:
		UUID m_ID;
		Constraint m_Constraint;
		ConstraintType m_ConstraintType = ConstraintType::Null;
	};


	class ConstraintAddedEvent : public ConstraintEvent
	{
	public:
		ConstraintAddedEvent(Constraint& constraint)
			: ConstraintEvent(constraint) {}

		EventType getEventType() const { return EventType::ConstraintAdded; }
		const char* getName() const { return "ConstraintAddedEvent"; }

		bool handleEvent() override
		{
			auto& world = World::getCurrentWorld();
			world.addConstraint(getConstraint());

			return true;
		}
	};

	class ConstraintRemovedEvent : public ConstraintEvent
	{
	public:
		ConstraintRemovedEvent(Constraint& constraint)
		{
			m_Constraint = constraint;
			m_ConstraintType = constraint.getConstraintType();
		}
		~ConstraintRemovedEvent() {}

		EventType getEventType() const { return EventType::ConstraintRemoved; }
		const char* getName() const { return "ConstraintRemovedEvent"; }

		bool handleEvent() override
		{
			auto& world = World::getCurrentWorld();
			auto& constraint = getConstraint();
			auto& rb = constraint.getRigidbody();
			world.removeConstraint(constraint);

			rb.getRigidbody()->forceActivationState(DISABLE_DEACTIVATION);
			rb.getRigidbody()->setDeactivationTime(0.0f);

			return true;
		}
	};


}
