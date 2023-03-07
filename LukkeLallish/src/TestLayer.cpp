#include "TestLayer.h"

#include "LukkelEngine/Core/Application.h"
#include "LukkelEngine/Editor/Editor.h"
#include "LukkelEngine/Scene/EntityFactory.h"

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
	
	glm::vec3 boxDims{ 2.0f, 2.0f, 2.0f };
	EntityFactory::createBox(boxDims, "Cube", *m_Scene);
	// spawner.createGround(*m_Scene, "Ground");
	// auto cube1 = spawner.createCube(*m_Scene, "Cube1");
	// auto cube2 = spawner.createCube(*m_Scene, "Cube2");
	// spawner.addConstraint(*m_Scene, cube1);
}

void TestLayer::onUpdate(float ts)
{			
	m_Scene->onUpdate(ts); // Fix the speed issue when using ts
}

void TestLayer::onImGuiRender()
{
	m_Scene->onImGuiRender();
	m_Editor->onImGuiRender();
}

void TestLayer::onEvent(LukkelEngine::Event& e)
{
}

void TestLayer::onDetach()
{
}
