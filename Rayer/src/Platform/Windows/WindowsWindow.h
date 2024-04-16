#pragma once

//Graphics context related headers
#include <Platform/OpenGL/OpenGLContext.h>

#include <glfw3.h>
#include <Rayer/Core/Window.h>


namespace Rayer {

	class WindowsWindow : public IWindow {

	public:

		WindowsWindow(const WindowProperties& windowProps, bool fullscreen = true);


		//Override the window interface methods
		virtual void Init(const WindowProperties& properties) override;
		virtual void OnUpdate() override;
		virtual void ClearFrame() override;
		virtual void PoolEvents() override;
		virtual void SwapBuffers() override;
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;
		virtual unsigned int GetWindowWidth() const override;
		virtual unsigned int GetWindowHeight() const override;
		virtual void* GetNativeWindow() override;
		virtual void SetFullScreenMode(bool fullscrenn) override;
	

	private:

		//glfw window for windows platform
		GLFWwindow* m_Window;

		//Window data structure
		struct WindowData {

			std::string w_Title;
			unsigned int w_Width;
			unsigned int w_Height;
			bool w_VSync;
		};
		
		//Main window data entity
		WindowData m_WindowData;
		
		//Graphics context associated with the window(Plaform independent).
		IGraphicsContext* graphicsContext;

		//Glfw initialization status
		static bool _glfwInitialized;


	};

}

