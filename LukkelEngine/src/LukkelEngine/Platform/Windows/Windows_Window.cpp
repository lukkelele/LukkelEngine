#include "LKpch.h"
#include "LukkelEngine/Platform/Windows/Windows_Window.h"
#include "LukkelEngine/Event/KeyEvent.h"
#include "LukkelEngine/Event/MouseEvent.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "LukkelEngine/Physics/World.h"


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
		// Initiate glfw
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
		setVSync(true);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GLFW_TRUE);

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double x, double y)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)x, (float)y);
			data.eventCallback(event);
		});

		// setInputLock(true);
		glfwSetWindowAttrib(m_Window, GLFW_FOCUSED, GL_TRUE);
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// Setup ImGui
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		// Font and enable keyboard
		io.Fonts->AddFontFromFileTTF("assets/fonts/SourceCodePro/SourceSansProSemibold.ttf", 20);
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui::StyleColorsDark();

		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
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

