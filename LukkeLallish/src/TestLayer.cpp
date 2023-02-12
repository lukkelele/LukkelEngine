#include "TestLayer.h"

#include "Entities/Rectangle.h"
#include "Entities/Cube.h"

#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

TestLayer::TestLayer()
	: Layer("TestLayer")
{
}

void TestLayer::onUpdate()
{
	LukkelEngine::Camera cam = m_Scene->getCamera();
	/* Poll input */
	if (LukkelEngine::Keyboard::isKeyPressed(LukkelEngine::Key::W))
	{
		LKLOG_INFO("W");
		cam.setPosition(glm::vec3(1, 2, 0));
	} 
	else if (LukkelEngine::Keyboard::isKeyPressed(LukkelEngine::Key::S))
	{
		cam.setPosition(glm::vec3(-1, -2, 0));
		LKLOG_INFO("S");
	} 
	if (LukkelEngine::Keyboard::isKeyPressed(LukkelEngine::Key::A)) 
	{
		LKLOG_INFO("A");
		cam.setPosition(glm::vec3(0, 0, 0));
	} 
	else if (LukkelEngine::Keyboard::isKeyPressed(LukkelEngine::Key::D))
	{
		LKLOG_INFO("D");
		cam.setPosition(glm::vec3(0, 0, 0));
	}

	auto sceneEntities = m_Scene->getEntities();
	for (auto& item : sceneEntities)
	{
		// glm::mat4 model = glm::translate(glm::mat4(1.0f), item->m_TranslationA);
		glm::vec3 translation = item->m_TranslationA;
		std::cout << translation.x << std::endl;
		cam.recalculateViewMatrix();
		auto mvp = cam.m_MVP;
		item->m_Shader->setUniformMat4f("camMatrix", mvp);
		// Shader matrix uniform -> camMatrix
	}

	m_Scene->onUpdate();
	onImGuiRender();
}

void TestLayer::onImGuiRender()
{
	ImGui::Text("Average FPS: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate); 
}

void TestLayer::onEvent(LukkelEngine::Event& e)
{

}

void TestLayer::onAttach()
{
	m_Scene = std::make_shared<LukkelEngine::Scene>();
	// LukkelEngine::Entity* Rect = new LukkelEngine::Rectangle();
	LukkelEngine::Entity* Cube = new LukkelEngine::Cube();
	Cube->m_Shader->setUniform4f("u_Color", 0.6f, 0.8f, 0.2f, 1.0f);
	// m_Scene->addEntity(*Rect);
	m_Scene->addEntity(*Cube);
}

void TestLayer::onDetach()
{

}
