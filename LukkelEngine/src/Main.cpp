#include <LukkelEngine/Core/Application.h>
#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "Platform/Windows/Windows_Window.h"
#include "Renderer/Camera.h"


/*
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
	 -50.0f, -50.0f, 0.0f, 0.0f,
	  50.0f, -50.0f, 1.0f, 0.0f,
	  50.0f,  50.0f, 1.0f, 1.0f,
	 -50.0f,  50.0f, 0.0f, 1.0f
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
	// glm::vec3 translationA(200, 200, 0);
	glm::vec3 translationA(0, 0, -100);
	glm::vec3 translationB(50, 0, 0);

	Camera cam(45, 1600, 1200, 0.01, 120.0f);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
	glm::mat4 proj = cam.getProjectionMatrix();
	glm::mat4 view = cam.getViewMatrix();

	glm::mat4 mvp = proj * view * model;

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	// ImGui::StyleColorsDark();

	shader.bind();
	shader.setUniformMat4f("camMatrix", mvp);
	texture.bind();
	shader.setUniform1i("u_Texture", 0);
	renderer.draw(vao, ibo, shader);

	LKLOG_CRITICAL("First draw");
	renderer.draw(vao, ibo, shader);
	LKLOG_WARN("Entering main loop");
	float sliderMax = 960;

	while (!glfwWindowShouldClose(window))
	{
		renderer.clear();

		ImGui_ImplGlfwGL3_NewFrame();
		ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, sliderMax); 
		ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, sliderMax);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		model = glm::translate(glm::mat4(1.0f), translationA);
		mvp = proj * view * model;
		shader.bind();
		shader.setUniformMat4f("camMatrix", mvp);

		renderer.draw(vao, ibo, shader);
		renderer.drawImGui();

		model = glm::translate(glm::mat4(1.0f), translationB);
		mvp = proj * view * model;
		shader.setUniformMat4f("camMatrix", mvp);

		renderer.draw(vao, ibo, shader);
		renderer.drawImGui();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}
*/
