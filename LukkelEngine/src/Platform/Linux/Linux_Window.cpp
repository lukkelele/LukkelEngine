#include "LKpch.h"
#include "Platform/Linux/Linux_Window.h"

#include "LukkelEngine/Event/KeyEvent.h"
#include "LukkelEngine/Event/MouseEvent.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_glfw_gl3.h"

namespace LukkelEngine {

	static bool GLFW_initialized = false;
	
	Linux_Window::Linux_Window(WindowProps& props)
	{
		init(props);
	}

	Linux_Window::~Linux_Window()
	{
		glfwTerminate();
	}

	void Linux_Window::init(WindowProps& props)
	{
		// Initiate glfw
		glfwInit();
		// Set core profile instead of compability one
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		// OPENGL Version 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glewExperimental = true; // needed for profile(?)

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
			GLenum err = glewInit();
			if (err != GLEW_OK) {
				// if error occured, print error message
				printf("[ERROR] %s\n", glewGetErrorString(err));
				GLFW_initialized = false;
			} else {
				printf("[OPENGL] Version: %s\n", glGetString(GL_VERSION));
				GLFW_initialized = true;
			}
		}
		setVSync(true);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GLFW_TRUE);
		glfwSetInputMode(m_Window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double x, double y)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)x, (float)y);
			data.eventCallback(event);
		});

		setInputLock(true);


		// Setup ImGui
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		// Add and load font
		io.Fonts->AddFontFromFileTTF("assets/fonts/SourceCodePro/SourceSansProSemibold.ttf", 20);
		// Enable keyboard
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		ImGui_ImplGlfwGL3_Init(m_Window, true);
		ImGui::StyleColorsDark();

	}
		
	void Linux_Window::exit()
	{
		GLCall(glfwDestroyWindow(m_Window));
	}

	void Linux_Window::onUpdate()
	{
		GLCall(glfwPollEvents());
		GLCall(glfwSwapBuffers(m_Window));
	}

	void Linux_Window::setVSync(bool enabled)
	{
		if (enabled) {
			glfwSwapInterval(1);
		} else {
			glfwSwapInterval(0);
		}
		m_Data.VSync = enabled;
	}

	bool Linux_Window::isVSync() const
	{
		return m_Data.VSync;
	}

	void Linux_Window::setInputLock(bool enabled)
	{
		m_InputLock = enabled;
		if (m_InputLock == false)
		{
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else if (m_InputLock == true)
		{
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}

	GLFWwindow* Linux_Window::getWindow() const { return m_Window; }


}
