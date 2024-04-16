#pragma once
#include <rpch.h>

#include <Rayer/Event/Event.h> //For the callback function



namespace Rayer {

	//Window property structure with default values
	struct WindowProperties {

		//Properties of the window
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		bool VSync;

		WindowProperties(std::string m_Title = "Rayer", unsigned int m_Width = 1920, unsigned int m_Height = 1080,bool m_VSync = true) : 
			Title(m_Title), 
			Width(m_Width), 
			Height(m_Height), 
			VSync(m_VSync) {}

	};


	//Window interface => Must be implemented by every platform specific window class(eg. Windows,Linux,Mac)
	class IWindow {

	public:

		using EventCallbackFn = std::function<void(Event&)>;

		//Window initialization method
		virtual void Init(const WindowProperties& _props) = 0;

		//Window related methods
		virtual void OnUpdate() = 0;
		virtual void ClearFrame() = 0;
		virtual void SwapBuffers() = 0;
		virtual void PoolEvents() = 0;
		
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		//Window data retrival methods
		virtual unsigned int GetWindowHeight() const = 0;
		virtual unsigned int GetWindowWidth() const = 0;
		virtual void* GetNativeWindow() = 0;
		virtual bool IsVSync() const = 0;

		//Window Property setting related methods
		virtual void SetVSync(bool enabled) = 0;
		virtual void SetFullScreenMode(bool fullscreen) = 0;

		static std::unique_ptr<IWindow> Create(const WindowProperties& props = WindowProperties());
		
	};

}