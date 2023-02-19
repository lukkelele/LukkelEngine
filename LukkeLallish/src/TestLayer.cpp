#include "TestLayer.h"

#include "LukkelEngine/Core/Application.h"

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
	Cube->m_Shader->setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
	m_Scene->addEntity(*Cube);
}

void TestLayer::onUpdate(float ts)
{			
	m_Scene->onUpdate(1.0f);
	onImGuiRender();
}

void TestLayer::onImGuiRender()
{
	auto cam = m_Scene->getCamera();
	ImGui::SliderFloat3("Object color", &colorSlider1.x, 0, 1.0f);
	m_Scene->getEntities().front()->m_Shader->setUniform4f("u_Color", colorSlider1.x, colorSlider1.y, colorSlider1.z, 1.0f);
	ImGui::SliderFloat("Camera speed", &cam->m_Speed, 0.010f, 2.0f);
	ImGui::SliderFloat("FOV", &cam->m_FOV, 25.0f, 120.0f);
	ImGui::Text("Average FPS: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate); 
}

void TestLayer::onEvent(LukkelEngine::Event& e)
{
}

void TestLayer::onDetach()
{
}
