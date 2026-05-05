#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"


namespace Hazel {

	class HAZEL_API Application {
	public:
		Application();

		virtual ~Application();

		void Run();

		void OnEvent(Event&);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		bool OnWindowClose(WindowCloseEvent& event);
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}