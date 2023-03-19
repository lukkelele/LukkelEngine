#include "TestLayer.h"

#include "LukkelEngine/Core/Application.h"
#include "LukkelEngine/Editor/EditorLayer.h"
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
	m_EditorLayer = create_s_ptr<EditorLayer>(m_Scene);
	
	glm::vec3 boxDims{ 2.0f, 2.0f, 2.0f };
	glm::vec3 smallerBoxDims{ 1.0f, 1.0f, 1.0f };
	glm::vec3 boxOffset{ 0.0f, 4.0f, 0.0f };
	glm::vec3 smallerBoxOffset{ 5.0f, 5.0f, 5.0f };

	glm::vec3 groundOffset{ 0.0f, -6.0f, 0.0f };
	glm::vec3 groundDims{ 50.0f, 2.0f, 50.0f };

	EntityProperties::Cube cubeProps("Cube", Rigidbody::Type::DYNAMIC, boxDims, boxOffset, 5.0f, Color::Cyan);
	EntityProperties::Cube smallerCubeProps("Smaller Cube", Rigidbody::Type::DYNAMIC, smallerBoxDims, smallerBoxOffset, 3.0f, Color::Red);
	EntityProperties::Cube groundProps("Ground", Rigidbody::Type::STATIC, groundDims, groundOffset, 0.0f, Color::Gray);

	EntityProperties::Sphere ballProps("Ball", Rigidbody::Type::DYNAMIC, 3.0f, groundOffset, 0.0f, Color::White);

	EntityFactory::createCube(groundProps);
	EntityFactory::createCube(cubeProps);
	EntityFactory::createCube(smallerCubeProps);
	// m_Scene->pause(true);
}

void TestLayer::onUpdate(float ts)
{			
	m_Scene->onUpdate(ts); // Fix the speed issue when using ts
}

void TestLayer::onImGuiRender()
{
	if (m_EditorLayer)
		m_EditorLayer->onImGuiRender();
	if (m_Scene)
		m_Scene->onImGuiRender();
}

void TestLayer::onEvent(LukkelEngine::Event& e)
{
}

void TestLayer::onDetach()
{
}
