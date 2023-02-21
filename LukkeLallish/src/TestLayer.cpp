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

	LukkelEngine::Entity* Cube = new LukkelEngine::Cube();
	Cube->m_Shader->setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

	// Set the scene to shared pointer
	m_Scene = LukkelEngine::Application::get().getScene();

	// Add cube to current scene
	LukkelEngine::EntityHandler::addEntity(*Cube);
}

void TestLayer::onUpdate(float ts)
{			
	m_Scene->onUpdate(1.0f);
	onImGuiRender();
}

void TestLayer::onImGuiRender()
{
}

void TestLayer::onEvent(LukkelEngine::Event& e)
{
}

void TestLayer::onDetach()
{
}
