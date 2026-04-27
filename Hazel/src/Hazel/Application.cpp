#include "pch_Hazel.h"
#include "Application.h"

namespace Hazel {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		Log::Init();
		WindowResizeEvent e(1280, 720);
		HZ_TRACE(e);

		while (true);
	}

}