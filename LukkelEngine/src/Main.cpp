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
// VERTEX COORD | TEXTURE COORDINATES
float rectangle_Tex[16] = {
-0.5f, -0.5f, 0.0f, 0.0f,
 0.5f, -0.5f, 1.0f, 0.0f,
 0.5f,  0.5f, 1.0f, 1.0f,
-0.5f,  0.5f, 0.0f, 1.0f
};
unsigned int rect_indices_Tex[6] = {
0, 1, 2,
2, 3, 0
};


int main()
{
	using namespace LukkelEngine;

	Application app;
	LKLOG_TRACE("Application created");
	// app.run();
	GLFWwindow* window = app.getWindow(); // debugging
	Renderer renderer;
	VertexArray vao = VertexArray();
	VertexBuffer vbo = VertexBuffer(rectangle_Tex, (sizeof(rectangle_Tex) / sizeof(float)) * sizeof(float));
	IndexBuffer ibo = IndexBuffer(rect_indices_Tex, (sizeof(rect_indices_Tex) / sizeof(unsigned int)) * sizeof(unsigned int));
	VertexBufferLayout layout;
	layout.push<float>(2);
	layout.push<float>(2);

	vao.addBuffer(vbo, layout);
	// Shader shader = Shader("res/shaders/basic2.shader");
	// shader.setUniform4f("u_Color", 0.5f, 0.1f, 0.5f, 1.0f);

	Texture texture = Texture("res/textures/tinder_logo.png");
	Shader shader = Shader("res/shaders/default3D.shader");

	shader.bind();
	texture.bind();
	shader.setUniform1i("u_Texture", 0);
	renderer.draw(vao, ibo, shader);

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
