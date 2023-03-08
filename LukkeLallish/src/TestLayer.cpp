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
	m_Editor = create_s_ptr<Editor>(m_Scene);
	
	glm::vec3 boxDims{ 2.0f, 2.0f, 2.0f };
	glm::vec3 boxOffset{ 0.0f, 6.0f, 0.0f };

	glm::vec3 groundOffset{ 0.0f, -6.0f, 0.0f };
	glm::vec3 groundDims{ 50.0f, 2.0f, 50.0f };

	auto box = EntityFactory::createBox(boxDims, boxOffset, "Cube", RigidBody::Type::DYNAMIC, *m_Scene);
	auto ground = EntityFactory::createBox(groundDims, groundOffset, "Ground", RigidBody::Type::STATIC, *m_Scene);
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
