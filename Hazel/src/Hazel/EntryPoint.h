#pragma once

#ifdef HZ_PLATFORM_WINDOWS

#include "Hazel/Log.h"

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	Hazel::Log::Init();
	std::cout << "Welcome to the Hazel Engine.\n";
	Hazel::Application* app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif // HZ_PLATFORM_WINDOWS