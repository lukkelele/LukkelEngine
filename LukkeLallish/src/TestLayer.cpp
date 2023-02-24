#include "TestLayer.h"

#include "LukkelEngine/Core/Application.h"
#include "LukkelEngine/Physics/TestObjects/Cube.h"

#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

TestLayer::TestLayer()
	: Layer("TestLayer")
{
}

void TestLayer::onAttach()
{
	using namespace LukkelEngine;
	m_Scene = Application::get().getScene();
	// LukkelEngine::Entity* Cube2 = new LukkelEngine::Cube();
	// LukkelEngine::Entity* Cube = new LukkelEngine::Cube();

	// UUID uuid();
	// Entity* cube = new Cube(uuid, *m_Scene);

	Entity* cube = new Cube();
	// m_Scene->m_Entities.push_back(*cube);
}

void TestLayer::onUpdate(float ts)
{			
	m_Scene->onUpdate(1.0f);
	m_Scene->onImGuiRender();
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
