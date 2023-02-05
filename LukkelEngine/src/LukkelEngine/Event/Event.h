#ifndef _EVENT_H
#define _EVENT_H
#include <LukkelEngine/Core/Base.h>
/* Include in precompiled header */
#include <string>
#include <sstream>
#include <functional>

namespace LukkelEngine {

	enum class EventType
	{
		null = 0,
		WindowFocus, WindowLostFocus, WindowMoved, WindowResize, WindowClose,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	/* - EventCategory -
	Categories can be sorted to log certain event types which is helpful in debugging.
	LK_BIT_FIELD is a bit field macro and is used to make an event tied to multiple
	categories. E.g a keyboard event is also a input event, hence placing the keyboard
	category below the input category.
	*/
	enum EventCategory
	{
		null = 0,
		EventCategoryApplication = LK_BIT_FIELD(0),
		EventCategoryInput		 = LK_BIT_FIELD(1),
		EventCategoryKeyboard	 = LK_BIT_FIELD(2),
		EventCategoryMouse		 = LK_BIT_FIELD(3),
		EventCategoryMouseButton = LK_BIT_FIELD(4)
	};

	#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; }\
								   virtual EventType getEventType() const override { return getStaticType(); }\
								   virtual const char* getName() const override { return #type; }

	#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

	class Event
	{
	public:
		virtual ~Event() = default;

		bool handled = false;

		virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual std::string toString() const { return getName(); }

		virtual int getCategoryFlags() const = 0;
		bool isInCategory(EventCategory category) { return getCategoryFlags() & category; }
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
			if (m_Event.getEventType() == T::getStaticType()) {
				m_Event.handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	/* Logging */
	inline std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.toString(); }
}

#endif /* _EVENT_H */