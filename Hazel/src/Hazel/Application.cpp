#include "pch_Hazel.h"

#include <GLFW/glfw3.h>

#include "Application.h"


namespace Hazel {

	Application::Application()
	{
		// With an std::unique_ptr there is no need do delete the object
		// when the destructor is called since that will be done automatically
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		HZ_TRACE(e);

		while (true)
		{
			m_Window->OnUpdate();
		}
	}

}