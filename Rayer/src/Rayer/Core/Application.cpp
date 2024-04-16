
#include <Rayer/Core/Application.h>

namespace Rayer {

	Application::Application() {

		m_Window = IWindow::Create();

		if (!m_Window) {

			std::cerr << "Application creation failed" << std::endl;
			std::terminate();
		}

	}

	void Application::ApplicationLoop() {


		while (m_Running) {

			m_Window->ClearFrame();
			m_Window->PoolEvents();

			m_Window->OnUpdate();

		}

	}

}
