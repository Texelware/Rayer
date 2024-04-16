#pragma once

#include "rpch.h"
#include <Rayer/Core/Core.h>
#include <functional>
#include <sstream>

namespace Rayer {

	//Event types for Rayer
	enum class EventType {

		None = 0,
		//Window events
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		//Key events
		KeyPressed, KeyReleased,
		//Rendering events
		AppTick, AppUpdate, AppRender,
		//Mouse events
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};


	//Event category for Rayer
	enum EventCategory {
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
                                virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


	class Event {

	public:

		friend class EventDispatcher;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const = 0;
		virtual int GetCategoryFlags() const = 0;

		bool IsInCategory(EventCategory category) {

			return GetCategoryFlags() & category;

		}

	public:

		bool m_Handled = false;

	};

	class EventDispatcher {

	private:
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event) : m_Event(event) {};

		template<typename T>
		bool Dispatch(EventFn<T> func) {

			if (m_Event.GetEventType() == T::GetStaticType()) {

				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}

			return false;

		}


	private:

		Event& m_Event;


	};



}