#pragma once
#include "LukkelEngine/Core/Base.h"


namespace LukkelEngine {

	enum class EventType
	{
		Null = 0,
		WindowFocus, WindowLostFocus, WindowMoved, WindowResize, WindowClose,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		// Physics
		ConstraintAdded, ConstraintRemoved, ConstraintAltered,
		RigidBodyAdded, RigidBodyRemoved, RigidBodyAltered,
	};

	class Event
	{
	public:
		virtual ~Event() = default;

		bool handled = false;

		virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual std::string toString() const { return getName(); }

	protected:
		// const char* m_Name;
		// EventType m_Type = EventType::Null;
	};
	/* 
		Dispatch events based on their type.
		Takes event references and can apply event type specific functions on the passed event.
	*/
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{ } 
		// F will be deduced by the compiler
		template<typename T, typename F>
		bool dispatch(const F& func)
		{
			return false;
		}
	private:
		Event& m_Event;
	};
}
