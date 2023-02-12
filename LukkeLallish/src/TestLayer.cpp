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
	//Rect->m_Shader->setUniform4f("u_Color", r, 0.5f, 0.5f, 1.0f);
	m_Scene->addEntity(*Rect);

	//LukkelEngine::Entity* Cube = new LukkelEngine::Cube();
	// Cube->m_Shader->bind();
	//m_Scene->addEntity(*Cube);
}

void TestLayer::onUpdate()
{			

	LukkelEngine::Camera cam = m_Scene->getCamera();
	/* Poll input */
	if (LukkelEngine::Keyboard::isKeyPressed(LukkelEngine::Key::W))
	{
		LKLOG_INFO("W");
		cam.setPosition(glm::vec3(0.5, 0.5, 0));
		r += 0.01;
	} 
	else if (LukkelEngine::Keyboard::isKeyPressed(LukkelEngine::Key::S))
	{
		cam.setPosition(glm::vec3(0.5, 0.2, 0));
		LKLOG_INFO("S");
		r -= 0.01;
	} 
	if (LukkelEngine::Keyboard::isKeyPressed(LukkelEngine::Key::A)) 
	{
		LKLOG_INFO("A");
		cam.setPosition(glm::vec3(-1, 0, 0));
	} 
	else if (LukkelEngine::Keyboard::isKeyPressed(LukkelEngine::Key::D))
	{
		LKLOG_INFO("D");
		cam.setPosition(glm::vec3(1, 0, 0));
	}


	auto sceneEntities = m_Scene->getEntities();
	for (auto &item : sceneEntities)
	{
		glm::vec3 translationA = item->m_TranslationA;
		item->m_Shader->bind();
		item->m_Shader->setUniformMat4f("u_ViewProjection", cam.getViewProjectionMatrix());
		item->m_Shader->setUniform4f("u_Color", r, 0.5f, 0.5f, 1.0f);
		cam.recalculateViewMatrix();
	}
	m_Scene->onUpdate();
	onImGuiRender();
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
