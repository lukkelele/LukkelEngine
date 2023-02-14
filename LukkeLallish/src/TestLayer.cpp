#include "TestLayer.h"

#include "Entities/Rectangle.h"
#include "Entities/Cube.h"

#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

TestLayer::TestLayer()
	: Layer("TestLayer")
{
}

void TestLayer::onAttach()
{
	m_Scene = std::make_shared<LukkelEngine::Scene>();

	LukkelEngine::Entity* Cube = new LukkelEngine::Cube();
	m_Scene->addEntity(*Cube);
}

void TestLayer::onUpdate(float ts)
{			
	LukkelEngine::s_ptr<LukkelEngine::Camera> cam = m_Scene->getCamera();

	//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	//glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	//glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	//glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
	//glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	//glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
	//glm::mat4 view;
	//view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
	//				   glm::vec3(0.0f, 0.0f, 0.0f),
	//				   glm::vec3(0.0f, 1.0f, 0.0f));

	//const float radius = 10.0f;
	//float camX = sin(glfwGetTime()) * radius;
	//float camZ = cos(glfwGetTime()) * radius;

	// Poll input
	auto entities = m_Scene->getEntities();
	auto cube = entities.front();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.5f, 0.5f, r));
	model = glm::rotate(model, glm::radians(40.0f), glm::vec3(1.0f, r, 0.5f));
	r += inc;
	if (r >= 1.0f || r <= 0)
		inc = -inc;
	cube->m_Shader->setUniformMat4f("model", model);

	cam->onUpdate(1.0f);

	onImGuiRender();
	m_Scene->onUpdate(1.0f);
}

void TestLayer::onImGuiRender()
{
	ImGui::SliderFloat("R color value", &r, 0, 1);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("Average FPS: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate); 
}

void TestLayer::onEvent(LukkelEngine::Event& e)
{
}

void TestLayer::onDetach()
{
}
