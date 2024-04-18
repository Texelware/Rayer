#pragma once

#include <Rayer/Event/Event.h>

namespace Rayer {


	class Layer {

	public:
		Layer(const std::string& name = "Layer");

		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		inline std::string GetName() const {
			return m_DebugName;
		}

	protected:
		std::string m_DebugName;


	};
}