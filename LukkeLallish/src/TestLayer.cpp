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

	//LukkelEngine::Entity* Rect = new LukkelEngine::Rectangle();
	//m_Scene->addEntity(*Rect);

	LukkelEngine::Entity* Cube = new LukkelEngine::Cube();
	m_Scene->addEntity(*Cube);
}

void TestLayer::onUpdate(float ts)
{			
	// auto cam = m_Scene->getCamera();
	LukkelEngine::s_ptr<LukkelEngine::Camera> cam = m_Scene->getCamera();

	// Poll input
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
