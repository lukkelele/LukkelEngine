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

	Entity cube = m_Scene->createEntity("Cube1");
	Entity cube2 = m_Scene->createEntity("Cube2");
	Entity floor = m_Scene->createEntity("floor");
	// Cube 1
	cube.addComponent<MeshComponent>();
	cube.addComponent<RigidBody3DComponent>(LK_TEMPLATE_OBJECT_CUBE);
	// Cube 2
	cube2.addComponent<MeshComponent>();
	cube2.addComponent<RigidBody3DComponent>(LK_TEMPLATE_OBJECT_CUBE);
	// Floor / ground
	floor.addComponent<MeshComponent>(2.0); // scaler
	floor.addComponent<RigidBody3DComponent>(LK_TEMPLATE_OBJECT_FLOOR, 2.0);
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
