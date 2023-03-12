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
	glm::vec3 smallerBoxDims{ 1.0f, 1.0f, 1.0f };
	glm::vec3 boxOffset{ 0.0f, 6.0f, 0.0f };
	glm::vec3 smallerBoxOffset{ 5.0f, 4.0f, 3.0f };

	glm::vec3 groundOffset{ 0.0f, -6.0f, 0.0f };
	glm::vec3 groundDims{ 50.0f, 2.0f, 50.0f };

	EntityProperties cubeProps("Cube", boxDims, boxOffset, 5.0f, RigidBody::Type::DYNAMIC, Color::Cyan);
	EntityProperties smallerCubeProps("Smaller Cube", smallerBoxDims, smallerBoxOffset, 3.0f, RigidBody::Type::DYNAMIC, Color::Red);
	EntityProperties groundProps("Ground", groundDims, groundOffset, 0.0f, RigidBody::Type::STATIC, Color::Gray);

	EntityFactory::createBox(groundProps, *m_Scene);
	EntityFactory::createBox(cubeProps, *m_Scene);
	EntityFactory::createBox(smallerCubeProps, *m_Scene);
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
