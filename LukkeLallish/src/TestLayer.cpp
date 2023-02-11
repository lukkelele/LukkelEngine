#include "TestLayer.h"
#include "TestCoordinates.h"

#include "Entities/Rectangle.h"

TestLayer::TestLayer()
	: Layer("TestLayer")
{
	std::shared_ptr<LukkelEngine::Shader> m_Shader;
	std::shared_ptr<LukkelEngine::VertexArray> m_VertexArray;


	LukkelEngine::Camera m_Camera;
}

void TestLayer::onUpdate(float t)
{
	m_Scene->onUpdate();
	onImGuiRender();
}

void TestLayer::onImGuiRender()
{
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate); 
}

void TestLayer::onEvent(LukkelEngine::Event& e)
{

}

void TestLayer::onAttach()
{
	m_Scene = std::make_shared<LukkelEngine::Scene>();
	LukkelEngine::Entity* Rect = new LukkelEngine::Rectangle();

	m_Scene->addEntity(*Rect);
}

void TestLayer::onDetach()
{

}
