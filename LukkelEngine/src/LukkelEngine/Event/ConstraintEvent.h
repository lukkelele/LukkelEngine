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
			m_ID = constraint.GetID();
			m_ConstraintType = constraint.GetConstraintType();
		}

		Constraint& getConstraint() { return m_Constraint; }
		Constraint::Type GetConstraintType() const { return m_ConstraintType; }
		UUID GetID() const { return m_ID; }

	protected:
		UUID m_ID;
		Constraint m_Constraint;
		Constraint::Type m_ConstraintType = Constraint::Type::Null;
	};


	class ConstraintAddedEvent : public ConstraintEvent
	{
	public:
		ConstraintAddedEvent(Constraint& constraint)
			: ConstraintEvent(constraint) {}

		EventType GetEventType() const { return EventType::ConstraintAdded; }
		const char* GetName() const { return "ConstraintAddedEvent"; }

		bool HandleEvent() override
		{
			auto& world = World::GetCurrentWorld();
			world.AddConstraint(getConstraint());

			return true;
		}
	};

	class ConstraintRemovedEvent : public ConstraintEvent
	{
	public:
		ConstraintRemovedEvent(Constraint& constraint)
		{
			m_Constraint = constraint;
			m_ConstraintType = constraint.GetConstraintType();
		}
		~ConstraintRemovedEvent() {}

		EventType GetEventType() const { return EventType::ConstraintRemoved; }
		const char* GetName() const { return "ConstraintRemovedEvent"; }

		bool HandleEvent() override
		{
			auto& world = World::GetCurrentWorld();
			auto& constraint = getConstraint();
			auto& rb = constraint.GetRigidbody();
			world.RemoveConstraint(constraint);

			rb.GetRigidbody()->forceActivationState(DISABLE_DEACTIVATION);
			rb.GetRigidbody()->setDeactivationTime(0.0f);

			return true;
		}
	};


}
