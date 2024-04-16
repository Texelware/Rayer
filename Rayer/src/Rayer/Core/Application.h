#pragma once
#include <rpch.h>

//Window related headers
#include <Platform/Windows/WindowsWindow.h>


namespace Rayer {
	

	//Main Application class
	class Application {

	public:

		Application();

		void ApplicationLoop();


	private:

		//Application running state
		bool m_Running = true;



		//Window object associated with this application (Platform independent)
		std::unique_ptr<IWindow> m_Window;

	};

	//Method to create the application object (Should be implemented by the client side
	Application* CreateApplication();

}