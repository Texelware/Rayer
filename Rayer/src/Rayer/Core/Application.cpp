
#include <Rayer/Core/Application.h>

namespace Rayer {

	#define BIND_EVENT_FN(x) std::bind(&Application::x , this , std::placeholders::_1)

	//Initialing the static instance variable
	Application* Application::s_Instance = nullptr;

	Application::Application() {

		m_Window = IWindow::Create();

		if (!m_Window) {

			std::cerr << "Application creation failed" << std::endl;
			std::terminate();
		}

		if (s_Instance == nullptr) {

			s_Instance = this;

		}

		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		

		//Allocating memory for the ImGui layer object
		m_ImGuiLayer = new ImGuiLayer();
		//Pushing it as an overlay
		PushOverlay(m_ImGuiLayer);
	
	}

	void Application::ApplicationLoop() {


		while (m_Running) {

			m_Window->ClearFrame();
			m_Window->PoolEvents();

			for (auto layer : m_LayerStack) {

				layer->OnUpdate();

			}

			m_ImGuiLayer->Begin();

				for (auto layer : m_LayerStack) {
					
					layer->OnImGuiRender();
				}

			m_ImGuiLayer->End();

			m_Window->OnUpdate();

		}

	}

	void Application::OnEvent(Event& e) {

		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(OnWindowClose));
		

	}

	bool Application::OnWindowClose(WindowClosedEvent& e) {

		m_Running = false;

		return true;
	}


	//Layer related methods defintions
	void Application::PushLayer(Layer* layer) {

		//Pushing to the layer stack and immidiately attaching it
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();

	}
	void Application::PushOverlay(Layer* overlay) {

		//Pushing to the layer stack and immidiately attaching it
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();

	}
	

}
