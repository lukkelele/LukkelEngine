#include "LKpch.h"
#include "LukkelEngine/Platform/Windows/Windows_Window.h"
#include "LukkelEngine/Event/KeyEvent.h"
#include "LukkelEngine/Event/MouseEvent.h"

#include "LukkelEngine/Physics/World.h"


namespace LukkelEngine {

	static bool GLFW_initialized = false;
	
	Windows_Window::Windows_Window(WindowProps& props)
	{
		Init(props);
	}

	Windows_Window::~Windows_Window()
	{
		glfwTerminate();
	}

	void Windows_Window::Init(WindowProps& props)
	{
		glfwInit();
		// Set core profile instead of compability one
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		// OPENGL Version 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		// Set window properties
		m_Data.title = props.title;
		m_Data.width = props.width;
		m_Data.height = props.height;
		m_Window = glfwCreateWindow((int)props.width, (int)props.height, props.title.c_str(), nullptr, nullptr);

		m_ViewportWidth = float(props.width);
		m_ViewportHeight = float(props.height);

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		
		if (!GLFW_initialized) {
			// GLenum err = glewInit();
			GLenum err = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			if (err == -1)
			{
				printf("There was an error starting GLAD");
			}
			else
			{
				printf("[OPENGL] Version: %s\n", glGetString(GL_VERSION));
				GLFW_initialized = true;
			}
		}
		SetVSync(true);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (glfwRawMouseMotionSupported())
			glfwSetInputMode(m_Window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

		glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GLFW_TRUE);

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double x, double y)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		});

		// setInputLock(true);
		glfwSetWindowAttrib(m_Window, GLFW_FOCUSED, GL_TRUE);
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
		
	void Windows_Window::Exit()
	{
		GLCall(glfwDestroyWindow(m_Window));
	}

	void Windows_Window::OnUpdate()
	{
		GLCall(glfwPollEvents());
		GLCall(glfwSwapBuffers(m_Window));
	}

	void Windows_Window::SetVSync(bool enabled)
	{
		if (enabled) {
			glfwSwapInterval(1);
		} else {
			glfwSwapInterval(0);
		}
		m_Data.vsync = enabled;
	}

	bool Windows_Window::IsVSync() const
	{
		return m_Data.vsync;
	}

	GLFWwindow* Windows_Window::GetWindow() const { return m_Window; }

}

