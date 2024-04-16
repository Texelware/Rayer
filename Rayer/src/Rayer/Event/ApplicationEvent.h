#pragma once
#include <Rayer/Event/Event.h>

namespace Rayer {

	class WindowResizedEvent : public Event {

	public:
		WindowResizedEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		virtual std::string ToString() const override {

			std::stringstream ss;
			ss << "Window resized : " << m_Width << "," << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_Width, m_Height;
	};

	class WindowMovedEvent : public Event {
	public:
		WindowMovedEvent(int x, int y)
			: m_X(x), m_Y(y) {}

		virtual std::string ToString() const override {

			std::stringstream ss;
			ss << "Window moved : " << m_X << "," << m_Y;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowMoved)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		int m_X, m_Y;

	};

	class WindowClosedEvent : public Event {
	public:

		WindowClosedEvent() {}

		virtual std::string ToString() const override {

			std::stringstream ss;
			ss << "Window closed!";
			return ss.str();
		}


		EVENT_CLASS_TYPE(WindowClose)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

}