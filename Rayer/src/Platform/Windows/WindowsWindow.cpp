#include "WindowsWindow.h"


namespace Rayer {

	bool WindowsWindow::_glfwInitialized = false;

	WindowsWindow::WindowsWindow(const WindowProperties& windowProps, bool fullscreen) {

		//Initializing our Windows window
		Init(windowProps);

		//Setting the window to fullscreen mode
		SetFullScreenMode(fullscreen);

	}


	void WindowsWindow::Init(const WindowProperties& _props) {

		//Setting up window properties for the Windows platform
		m_WindowData.w_Title = _props.Title;
		m_WindowData.w_Width = _props.Width;
		m_WindowData.w_Height = _props.Height;
		m_WindowData.w_VSync = _props.VSync;

		//Initializing glfw
		if (!_glfwInitialized) {
			int success = glfwInit();

			if (!success) {

				std::cout << "Failed to initialize GLFW" << std::endl;
				exit(1);
			}

			else {
				std::cout << " GLFW Successfully initialized" << std::endl;
				_glfwInitialized = true;
			}
		}


		//Window creation hint for glfw
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


		//Creating actual window for windows
		m_Window = glfwCreateWindow(m_WindowData.w_Width, m_WindowData.w_Height, m_WindowData.w_Title.c_str(), nullptr, nullptr);

		//Iniltializing graphics context
		graphicsContext = new OpenGLContext(m_Window);
		graphicsContext->Init();

		//Setting glfw window data
		glfwSetWindowUserPointer(m_Window, &m_WindowData);

		//Setting VSync
		SetVSync(m_WindowData.w_VSync);

	}


	void WindowsWindow::SetVSync(bool enabled) {

		if (enabled) {

			glfwSwapInterval(1);
		}

		else {
			
			glfwSwapInterval(0);
		}

	}

	void WindowsWindow::SwapBuffers() {

		graphicsContext->SwapBuffers();

	}

	void WindowsWindow::ClearFrame() {

		glClearColor(1.0f, 0.2f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

	}

	void WindowsWindow::PoolEvents() {

		glfwPollEvents();

	}

	void WindowsWindow::OnUpdate() {

		SwapBuffers();

	}

	void* WindowsWindow::GetNativeWindow() {

		return (void*)m_Window;
	}

	unsigned int WindowsWindow::GetWindowHeight() const {

		return m_WindowData.w_Height;
	}

	unsigned int WindowsWindow::GetWindowWidth() const {

		return m_WindowData.w_Width;
	}

	bool WindowsWindow::IsVSync() const {

		return m_WindowData.w_VSync;
	}

	void WindowsWindow::SetFullScreenMode(bool fullscreen) {

		if (fullscreen) {

			glfwMaximizeWindow(m_Window);
		}

	}
	
}