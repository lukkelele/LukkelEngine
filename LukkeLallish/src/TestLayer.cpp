#include "TestLayer.h"

#include "LukkelEngine/Core/Application.h"
#include "LukkelEngine/Scene/Editor.h"
#include "LukkelEngine/Scene/Spawner.h"
// #include "LukkelEngine/Physics/KinematicRigidBodyExample.h"

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
	Spawner spawner;
	// Level Editor
	m_Editor = create_s_ptr<Editor>(m_Scene);

	spawner.createGround(*m_Scene, "Ground");
	auto cube = spawner.createCube(*m_Scene, "Cube");
	// spawner.addConstraint(*m_Scene, cube);
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
