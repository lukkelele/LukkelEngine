#include "Platform/Windows/Windows_Window.h"
#include "LukkelEngine/Event/KeyEvent.h"
#include "LukkelEngine/Event/MouseEvent.h"

namespace LukkelEngine {

	static bool GLFW_initialized = false;
	
	Windows_Window::Windows_Window(WindowProps& props)
	{
		init(props);
	}

	Windows_Window::~Windows_Window()
	{
		glfwTerminate();
	}

	void Windows_Window::init(WindowProps& props)
	{
		/* Initiate glfw */
		glfwInit();
		/* Set core profile instead of compability one */
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		/* OPENGL Version 3.3 */
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glewExperimental = true; // needed for profile(?)

		/* Set window properties */
		m_Data.title = props.title;
		m_Data.width = props.width;
		m_Data.height = props.height;
		m_Window = glfwCreateWindow((int)props.width, (int)props.height, props.title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		
		if (!GLFW_initialized) {
			GLenum err = glewInit();
			if (err != GLEW_OK) {
				/* if error occured, print error message */
				printf("[ERROR] %s\n", glewGetErrorString(err));
				GLFW_initialized = false;
			} else {
				printf("[OPENGL] Version: %s\n", glGetString(GL_VERSION));
				GLFW_initialized = true;
			}
		}
		setVSync(true);
		glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, 1);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		// {
		// 	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		// 	switch (action) 
		// 	{
		// 		case GLFW_PRESS:
		// 		{
		// 			MouseButtonPressedEvent event(button);
		// 			data.eventCallback(event);
		// 			break;
		// 		}
		// 		case GLFW_RELEASE:
		// 		{
		// 			MouseButtonReleasedEvent event(button);
		// 			data.eventCallback(event);
		// 			break;
		// 		}
		// 	}
		// });

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double x, double y)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)x, (float)y);
			data.eventCallback(event);
		});

		//glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		//{
		//	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		//	MouseMovedEvent event((float)xPos, (float)yPos);
		//	data.eventCallback(event);
		//});

	}
		
	void Windows_Window::exit()
	{
		GLCall(glfwDestroyWindow(m_Window));
	}

	void Windows_Window::onUpdate()
	{
		GLCall(glfwPollEvents());
		GLCall(glfwSwapBuffers(m_Window));
	}

	void Windows_Window::setVSync(bool enabled)
	{
		if (enabled) {
			glfwSwapInterval(1);
		} else {
			glfwSwapInterval(0);
		}
		m_Data.VSync = enabled;
	}

	bool Windows_Window::isVSync() const
	{
		return m_Data.VSync;
	}

	GLFWwindow* Windows_Window::getWindow() const { return m_Window; }

}

