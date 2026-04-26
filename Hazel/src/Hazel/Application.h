#pragma once

#include "Core.h"
#include "Log.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"


namespace Hazel {

	class HAZEL_API Application {
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	Application* CreateApplication();

}