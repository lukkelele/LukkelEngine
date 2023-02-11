#include "TestLayer.h"

#include "Entities/Rectangle.h"

TestLayer::TestLayer()
	: Layer("TestLayer")
{
}

void TestLayer::onUpdate()
{
	/* Poll input */
	if (LukkelEngine::Keyboard::isKeyPressed(LukkelEngine::Key::W))
		LKLOG_BLUE("W");
	else if (LukkelEngine::Keyboard::isKeyPressed(LukkelEngine::Key::S))
		LKLOG_BLUE("S");
	if (LukkelEngine::Keyboard::isKeyPressed(LukkelEngine::Key::A))
		LKLOG_BLUE("A");
	else if (LukkelEngine::Keyboard::isKeyPressed(LukkelEngine::Key::D))
		LKLOG_BLUE("D");

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
	LukkelEngine::Entity* Rect = new LukkelEngine::Rectangle();

	m_Scene->addEntity(*Rect);
}

void TestLayer::onDetach()
{

}
