#pragma once

#include "pch_Hazel.h"

#include "Hazel/Core.h"


namespace Hazel {

	// Events in Hazel are currently blocking - meaning when an event occurs, it
	// immediately gets dispatched and must be resolved before the app may carry on.
	// In the future, a better strategy might be to buffer events in an event bus,
	// and process them during the "event" part of the update stage.

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// Each event can belong to more than one category
	// For example, a mouse-event will also be an input-event
	// EventCategory allows flagging multiple categories using simple bit-shifts
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput		 = BIT(1),
		EventCategoryKeyboard	 = BIT(2),
		EventCategoryMouse		 = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static  EventType   GetStaticType()	{ return EventType::##type; }\
							   virtual EventType   GetEventType()   const override { return GetStaticType(); }\
							   virtual const char* GetName()		const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class HAZEL_API Event {
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); };

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

		inline bool Handled() const { return m_Handled; }

	protected:
		bool m_Handled = false;
	};

	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : m_Event(event) {}

		template<typename SomeEventType>
		bool Dispatch(EventFn<SomeEventType> func)
		{
			if (m_Event.GetEventType() == SomeEventType::GetStaticType())
			{
				m_Event.m_Handled = func(*((SomeEventType*) &m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& event)
	{
		return os << event.ToString();
	}

	inline std::string format_as(const Event& event) { return event.ToString(); }
}