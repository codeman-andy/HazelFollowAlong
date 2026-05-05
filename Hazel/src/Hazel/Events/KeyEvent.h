#pragma once

#include "Event.h"


namespace Hazel {

	class HAZEL_API KeyEvent : public Event {
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		int m_KeyCode;
		KeyEvent(int key_code) : m_KeyCode(key_code) {}
	};

	// KeyPressedEvent not only represents when a given key has been pressed, but it
	// also facilitates the detection of KeyRepeatedEvents (i.e. the user is holding down a key)
	// m_RepeatCount can also be turned into a bool to signal whether it is the first time the key
	// has been pressed, or whether it is a KeyRepeatedEvent
	class HAZEL_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int key_code, int repeat_count) : KeyEvent(key_code), m_RepeatCount(repeat_count) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (with " << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount;
	};

	class HAZEL_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int key_code) : KeyEvent(key_code) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

}