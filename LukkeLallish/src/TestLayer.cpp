#include "TestLayer.h"

#include "LukkelEngine/Core/Application.h"
#include "LukkelEngine/Scene/ObjectHandler.h"
#include "LukkelEngine/Scene/Editor.h"

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

	// Level Editor
	m_Editor = create_s_ptr<Editor>(m_Scene);

	// Add new objects to the scene
	ObjectHandler::addFloor(*m_Scene, "Floor");
	ObjectHandler::addCube(*m_Scene, "Cube");
	// ObjectHandler::addCube(*m_Scene, "Cube2");
}

void TestLayer::onUpdate(float ts)
{			
	m_Scene->onUpdate(1.0f); // Fix the speed issue when using ts
}

void TestLayer::onImGuiRender()
{
	m_Scene->onImGuiRender();
	m_Editor->displayMenu();
}

void TestLayer::onEvent(LukkelEngine::Event& e)
{
}

void TestLayer::onDetach()
{
}
