#pragma once

#include <Rayer/Event/Event.h>


namespace Rayer {

	class KeyPressedEvent : public Event {

	public:
		KeyPressedEvent(int keyCode, int repeatCount) : KeyCode(keyCode), RepeatCount(repeatCount) {}

		virtual std::string ToString() const override {

			std::stringstream ss;
			ss << "KeyPressedEvent: " << KeyCode << "(KeyCode), " << RepeatCount << "(RepeatCount)";
			return ss.str();
		}

		inline int GetRepeatCount() const { return RepeatCount; }
		inline int GetKeyCode() const { return KeyCode; }

		EVENT_CLASS_TYPE(KeyPressed)
			EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	private:
		int KeyCode, RepeatCount;
	};

	class KeyReleasedEvent : public Event {

	public:

		KeyReleasedEvent(int keyCode) : KeyCode(keyCode) {}

		virtual std::string ToString() const override {

			std::stringstream ss;
			ss << "KeyReleasedEvent: " << KeyCode << "(KeyCode)";
			return ss.str();

		}

		inline int GetKeyCode() const { return KeyCode; }

		EVENT_CLASS_TYPE(KeyReleased)
			EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	private:

		int KeyCode;

	};

}