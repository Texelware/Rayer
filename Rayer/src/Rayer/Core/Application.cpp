
#include <Rayer/Core/Application.h>

namespace Rayer {

	#define BIND_EVENT_FN(x) std::bind(&Application::x , this , std::placeholders::_1)

	Application::Application() {

		m_Window = IWindow::Create();

		if (!m_Window) {

			std::cerr << "Application creation failed" << std::endl;
			std::terminate();
		}

		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	
	}

	void Application::ApplicationLoop() {


		while (m_Running) {

			m_Window->ClearFrame();
			m_Window->PoolEvents();

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

}
