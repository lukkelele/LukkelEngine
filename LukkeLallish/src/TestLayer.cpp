#include "TestLayer.h"
#include "TestCoordinates.h"


TestLayer::TestLayer()
	: Layer("TestLayer")
{
	std::shared_ptr<LukkelEngine::Shader> m_Shader;
	std::shared_ptr<LukkelEngine::VertexArray> m_VertexArray;

	LukkelEngine::Camera m_Camera;
	LukkelEngine::Scene m_Scene;

}

void TestLayer::onUpdate(float t)
{
	m_Scene->onUpdate();
}

void TestLayer::onImGuiRender()
{

}

void TestLayer::onEvent(LukkelEngine::Event& e)
{

}

void TestLayer::onAttach()
{
	LKLOG_WARN("onAttach() called");
	LukkelEngine::Scene* scene = new LukkelEngine::Scene;
	m_Scene = scene;
	std::shared_ptr<LukkelEngine::Entity> Rectangle = std::make_shared<LukkelEngine::Entity>();

	// Add some properties to this rectangle
	auto va = LukkelEngine::VertexArray();
	auto vb = LukkelEngine::VertexBuffer(rectangle, (sizeof(rectangle) / (sizeof(float)) * sizeof(float)));
	auto ib = LukkelEngine::IndexBuffer(rectangle_indices, (sizeof(rectangle_indices) / sizeof(unsigned int)) * sizeof(unsigned int));
	auto layout = LukkelEngine::VertexBufferLayout();
	layout.push<float>(2);
	va.addBuffer(vb, layout);


	auto shader = LukkelEngine::Shader("res/shaders/3D/color3D.shader");
	shader.bind();
	shader.setUniform4f("u_Color", 0.5f, 0.8f, 0.5f, 1.0f);

	Rectangle->setVertexArray(va);
	Rectangle->setVertexBuffer(vb);
	Rectangle->setIndexBuffer(ib);
	Rectangle->setVertexShader(shader);
	Rectangle->getVertexArray();
	LKLOG_TRACE("Done setting up Rectangle properties");

	scene->addEntity(Rectangle);
}

void TestLayer::onDetach()
{

}
