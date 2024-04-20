#pragma once
#include <rpch.h>

#include <Rayer/Core/Core.h>

//ImGui Layer
#include <Rayer/Layer/ImGuiLayer.h>

//Window related headers
#include <Platform/Windows/WindowsWindow.h>

//Header to include the layerstack
#include <Rayer/Core/LayerStack.h>





namespace Rayer {
	


	//Main Application class
	class Application {

	public:

		Application();

		void ApplicationLoop();

		//Event handler methods
		void OnEvent(Event& e);

		//Window related callback methods
		bool OnWindowClose(WindowClosedEvent& e);


		//Layer related methods
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		
		
		//Singleton refrence getter method
		static Application& Get() {

			return *s_Instance;
		}

		//Method to get the native window for the current platform
		void* GetNativeWindow() {

			return m_Window->GetNativeWindow();

		}


		IWindow& GetWindow() {

			return *m_Window.get();
		}



	private:



		//Application running state
		bool m_Running = true;

		//LayerStack onject
		LayerStack m_LayerStack;

		//Window object associated with this application (Platform independent)
		Scope<IWindow> m_Window;

		//For the single instance of the application
		static Application* s_Instance;

		//ImGuiLayer object
		ImGuiLayer* m_ImGuiLayer;

	};

	//Method to create the application object (Should be implemented by the client side
	Application* CreateApplication();

}