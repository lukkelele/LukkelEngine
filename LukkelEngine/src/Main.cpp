#include <LukkelEngine/Core/Application.h>
#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "Platform/Windows/Windows_Window.h"
#include "Renderer/Camera.h"

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
	glEnable(GL_DEPTH_TEST);
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
	glm::vec3 translationA(200, 200, 0);
	glm::vec3 translationB(400, 200, 0);

	Camera cam();
	glm::mat4 testMat = glm::translate(glm::mat4(0.5f), glm::vec3(1, 0, 0));

	shader.bind();
	shader.setUniformMat4f("camMatrix", testMat);
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
