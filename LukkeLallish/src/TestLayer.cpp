#include "TestLayer.h"

#include "LukkelEngine/Core/Application.h"
#include "LukkelEngine/Scene/ObjectHandler.h"

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
	ObjectHandler::addFloor(*m_Scene, "Floor");
	ObjectHandler::addCube(*m_Scene, "Cube1");
	// ObjectHandler::addCube(*m_Scene, "Cube2");
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
