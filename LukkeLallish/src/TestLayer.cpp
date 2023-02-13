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
	LukkelEngine::Entity* Rect = new LukkelEngine::Rectangle();
	m_Scene->addEntity(*Rect);

	//LukkelEngine::Entity* Cube = new LukkelEngine::Cube();
	// Cube->m_Shader->bind();
	//m_Scene->addEntity(*Cube);
}

void TestLayer::onUpdate()
{			

	/* Poll input */
	if (LukkelEngine::Keyboard::isKeyPressed(LukkelEngine::Key::W))
	{
		LKLOG_INFO("W");
		m_Scene->updateCameraPosition(glm::vec3(0.0f, -1.0f, 0.0f));
		r += 0.01;
	} 
	else if (LukkelEngine::Keyboard::isKeyPressed(LukkelEngine::Key::S))
	{
		m_Scene->updateCameraPosition(glm::vec3(0.0f, 1.0f, 0.0f));
		LKLOG_INFO("S");
		r -= 0.01;
	} 
	if (LukkelEngine::Keyboard::isKeyPressed(LukkelEngine::Key::A)) 
	{
		LKLOG_INFO("A");
		m_Scene->updateCameraPosition(glm::vec3(1.0f, 0.0f, 0.0f));
		b -= 0.1f;
	} 
	else if (LukkelEngine::Keyboard::isKeyPressed(LukkelEngine::Key::D))
	{
		LKLOG_INFO("D");
		m_Scene->updateCameraPosition(glm::vec3(-1.0f, 0.0f, 0.0f));
		b += 0.1f;
	}

	auto cam = m_Scene->getCamera();

	auto sceneEntities = m_Scene->getEntities();
	for (auto &item : sceneEntities)
	{
		glm::vec3 translationA = item->m_TranslationA;
		cam.recalculateViewMatrix();
		item->m_Shader->bind();
		item->m_Shader->setUniformMat4f("u_ViewProjection", cam.getViewProjectionMatrix());
		item->m_Shader->setUniform4f("u_Color", r, b, 0.2f, 1.0f);
	}
	onImGuiRender();
	m_Scene->onUpdate();
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
