#include "TestLayer.h"

#include "LukkelEngine/Core/Application.h"

#include "Entities/Rectangle.h"
#include "Entities/Cube.h"
#include "LukkelEngine/Physics/WorldPhysics.h"

#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

TestLayer::TestLayer()
	: Layer("TestLayer")
{
}

void TestLayer::onAttach()
{
	m_Scene = LukkelEngine::Application::get().getScene();

	LukkelEngine::Entity* Cube2 = new LukkelEngine::Cube();
	LukkelEngine::Entity* Cube = new LukkelEngine::Cube();
	Cube2->m_Shader->setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
	Cube->m_Shader->setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

	LukkelEngine::EntityHandler::addEntity(*Cube);
	LukkelEngine::EntityHandler::addEntity(*Cube2);
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
