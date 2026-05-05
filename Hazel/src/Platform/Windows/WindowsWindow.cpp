#include "pch_Hazel.h"

#include "WindowsWindow.h"


namespace Hazel {

	static bool s_GLFWInitialized = false;

	// The choice for being static: multiple windows each needs its own data structure, but can share a common error function
	static void GLFWErrorCallback(int error, const char* description)
	{
		HZ_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProperties& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProperties& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		HZ_CORE_INFO("Creating Window {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			// glfwInit()'s result is stored into a local variable so it can be passed into HZ_CORE_ASSERT
			// Otherwise glfwInit() would have to be passed, and once we would compile on anything other
			// than Debug-mode, the line would be removed and thus glfwInit()'s instruction along with it
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not initialize GLFW!");
			// For the error callback our function is static, so there is never a need to capture 'this->'
			// so that we may access our m_Data member
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW Callbacks
		// GLFW callbacks are C functions, and C knows nothing about the this->pointer or class-instances (since all calls
		// through instanced objects have an implicit argument to this->), so to get the data inside our
		// WindowsWindow-object we first handed its m_Data member to GLFW's WindowUserPointer
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *((WindowData*) glfwGetWindowUserPointer(window));
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *((WindowData*) glfwGetWindowUserPointer(window));

				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *((WindowData*) glfwGetWindowUserPointer(window));

				switch (action)
				{
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						// GLFW does not provide a repeat count, like it does with the key, scancode, action and mods variables
						// 1 will be used as a placeholder but it is possible in the future to extract this repeat count
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *((WindowData*) glfwGetWindowUserPointer(window));

				switch (action)
				{
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
						break;
					}
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double x_offset, double y_offset)
			{
				WindowData& data = *((WindowData*) glfwGetWindowUserPointer(window));

				MouseScrolledEvent event((float) x_offset, (float) y_offset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x_position, double y_position)
			{
				WindowData& data = *((WindowData*) glfwGetWindowUserPointer(window));

				MouseMovedEvent event((float) x_position, (float) y_position);
				data.EventCallback(event);
			});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		// We track whether VSync is enabled or not ourselves because this info is not kept by GLFW
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}