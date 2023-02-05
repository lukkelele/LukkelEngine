#include <LKpch.h>
#include <Windows/Windows_Window.h>

namespace LukkelEngine {
	static bool GLFW_initialized = false;
	
	Windows_Window::Windows_Window(){}

	Windows_Window::Windows_Window(WindowProps& props)
	{
		init(props);
	}

	Windows_Window::~Windows_Window()
	{
		GLCall(glfwTerminate());
	}

	void Windows_Window::init(WindowProps& props)
	{
		/* Initiate glfw */
		glfwInit();
		/* Set core profile instead of compability one */
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		/* Version 3.3 */
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glewExperimental = true; // needed for profile(?)
		/* Set window properties */
		m_Data.title = props.title;
		m_Data.width = props.width;
		m_Data.height = props.height;
		m_Window = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		GLCall(glfwSetWindowUserPointer(m_Window, &m_Data));

		if (!GLFW_initialized) {
			// TODO: Fix here so Log is initialized
			// LK_TRACE("Initializing glew");
			GLenum err = glewInit();
			if (err != GLEW_OK) {
				/* if error occured, print error message */
				printf("Error: %s\n", glewGetErrorString(err));
				// LK_ERROR("Error: {0}", glewGetErrorString(err));
				// TODO: Fix here so Log is initialized
				GLFW_initialized = true;
			} else {
				// TODO: Fix here so Log is initialized
				printf("openGL version: %s\n", glGetString(GL_VERSION)); /* output openGL version */
				// LK_TRACE("OpenGL version: {0}", glGetString(GL_VERSION)); /* output openGL version */
				GLFW_initialized = false;
			}
		}
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
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
		} else {
			GLCall(glfwSwapInterval(0));
		}
		m_Data.VSync = enabled;
	}

	bool Windows_Window::isVSync() const
	{
		return m_Data.VSync;
	}

	GLFWwindow* Windows_Window::getWindow() const { return m_Window; }

	Window* Window::create(WindowProps& props)
	{
		Window* window = dynamic_cast<Window*>(new Windows_Window(props));
		return window;
	}

	inline void Windows_Window::setCallback()
	{

	}
}

