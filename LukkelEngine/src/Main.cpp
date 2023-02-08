#include <LukkelEngine/Core/Application.h>
#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "Platform/Windows/Windows_Window.h"

float rectangle[8] = {
	-0.5f, -0.5f,
	 0.5f, -0.5f,
	 0.5f,  0.5f,
	-0.5f,  0.5f
};
unsigned int rect_indices[6] = {
	0, 1, 2,
	2, 3, 0
};

int main()
{
	using namespace LukkelEngine;
	// LukkeLog::Log::init();
	// glfwInit();
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// /* Version 3.3 */
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// glewExperimental = true; // needed for profile(?)
	// /* Set window properties */
	// // m_Data.title = props.title;
	// // m_Data.width = props.width;
	// // m_Data.height = props.height;
	// GLFWwindow* window = glfwCreateWindow(800, 600, "Main", nullptr, nullptr);
	// glfwMakeContextCurrent(window);
	// // GLCall(glfwSetWindowUserPointer(m_Window, &m_Data));
	// // glfwSetWindowUserPointer(window, &m_Data);
	// 
	// GLenum err = glewInit();
	// if (err != GLEW_OK) {
	// 	/* if error occured, print error message */
	// 	printf("[ERROR] %s\n", glewGetErrorString(err));
	// } else {
	// 	printf("[OPENGL] Version: %s\n", glGetString(GL_VERSION)); /* output openGL version */
	// }


	Application app;
	// LKLOG_TRACE("Application created");
	// app.run();
	GLFWwindow* window = app.getWindow();
	// Windows_Window win = Windows_Window(WindowProps());
	// GLFWwindow* window = win.getWindow();
	Renderer renderer;
	VertexArray vao = VertexArray();
	VertexBuffer vbo = VertexBuffer(rectangle, 8 * sizeof(float));
	IndexBuffer ibo = IndexBuffer(rect_indices, 3);
	VertexBufferLayout layout;
	layout.push<float>(2);

	vao.addBuffer(vbo, layout);
	Shader shader = Shader("res/shaders/basic2.shader");
	shader.bind();
	shader.setUniform4f("u_Color", 0.5f, 0.1f, 0.5f, 1.0f);

	LKLOG_CRITICAL("First draw");
	renderer.draw(vao, ibo, shader);
	LKLOG_WARN("Entering main loop");

	while (!glfwWindowShouldClose(window))
	{
		renderer.clear();
		renderer.draw(vao, ibo, shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	

	return 0;
}
