#include "pch_Hazel.h"

#include <GLFW/glfw3.h>

#include "Application.h"


namespace Hazel {

// BIND_EVENT_FN(x) in Cherno's series
#define BIND_EVENT_CALLBACK_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
// Binds to a pointer to a member function
// &Application::x points to the address of the member function
// Because member-functions need an initialized class instance 'this' will always be an implicit argument the member function will need
// std::placeholders_1 holds the place for the unbound argument (i.e. event) which will only be defined in later calls

	Application::Application()
	{
		// With an std::unique_ptr there is no need do delete the object
		// when the destructor is called since that will be done automatically
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_CALLBACK_FN(OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		HZ_TRACE(e);

		while (m_Running == true)
		{
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_CALLBACK_FN(OnWindowClose));

		HZ_CORE_TRACE("{0}", event);
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}

}