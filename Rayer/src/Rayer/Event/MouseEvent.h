#pragma once

#include <Rayer/Event/Event.h>

namespace Rayer {

	class MouseMovedEvent : public Event {

	public:

		MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

		virtual std::string ToString() const override {

			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)


	private:

		float m_MouseX, m_MouseY;

	};

	class MouseScrolledEvent : public Event {


	public:

		MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

		virtual std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:

		float m_XOffset, m_YOffset;

	};

	class MouseButtonPressedEvent : public Event {


	public:

		MouseButtonPressedEvent(int button) : m_Button(button) {}

		virtual std::string ToString() const override {

			std::stringstream ss;
			ss << "MouseButtonPressed: " << m_Button << "(KeyCode)";
			return ss.str();

		}

		inline int GetButton() const { return m_Button; }

		EVENT_CLASS_TYPE(MouseButtonPressed)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)


	private:

		int m_Button;


	};


	class MouseButtonReleasedEvent : public Event {

	public:

		MouseButtonReleasedEvent(int button) : m_Button(button) {}

		virtual std::string ToString() const override {

			std::stringstream ss;
			ss << "MouseButtonReleased: " << m_Button << "(KeyCode)";
			return ss.str();

		}

		inline int GetButton() const { return m_Button; }

		EVENT_CLASS_TYPE(MouseButtonReleased)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)


	private:
		int m_Button;

	};



}
