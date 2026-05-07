#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"


namespace Hazel {

	class HAZEL_API Application {
	public:
		Application();

		virtual ~Application();

		void Run();

		void OnEvent(Event&);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* Overlay);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack; // Created on the stack so it will have the life-time of the Application-class

		bool OnWindowClose(WindowCloseEvent& event);
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}