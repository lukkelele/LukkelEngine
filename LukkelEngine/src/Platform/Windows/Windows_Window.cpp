#include <Windows/Windows_Window.h>


namespace LukkelEngine {

	static bool GLFW_initialized = false;

	Windows_Window::Windows_Window(WindowProps& props)
	{
		init(props);
	}

	Window* Window::create(WindowProps& props)
	{

	}

	void Windows_Window::init(WindowProps& props)
	{
		m_Data.title = props.title;
		m_Data.width = props.width;
		m_Data.height = props.height;
		LOG("Creating window");
		if (!GLFW_initialized) {
			GLCall(GLenum err = glewInit());
			if (err != GLEW_OK) {
				/* if error occured, print error message */
				printf("Error: %s\n", glewGetErrorString(err));
				GLFW_initialized = true;
			} else {
				printf("openGL version: %s\n", glGetString(GL_VERSION)); /* output openGL version */
				GLFW_initialized = false;
			}
		}
		m_Window = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, nullptr);
		GLCall(glfwMakeContextCurrent(m_Window));
		GLCall(glfwSetWindowUserPointer(m_Window, &m_Data));
		setVSync(true);
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
			GLCall(glfwSwapInterval(1));
		} else
			GLCall(glfwSwapInterval(0));
		m_Data.VSync = enabled;
	}

	bool Windows_Window::isVSync() const
	{
		return m_Data.VSync;
	}

	void Windows_Window::initImGui()
	{
		ImGui::CreateContext();
		// ImGui_ImplGlfwGL3_Init(m_Window, true);
		ImGui::StyleColorsDark();
	}

	GLFWwindow* Windows_Window::getWindow() const { return this->m_Window; }
}
