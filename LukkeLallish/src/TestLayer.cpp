#include "TestLayer.h"
#include "TestCoordinates.h"


TestLayer::TestLayer()
	: Layer("TestLayer")
{
	std::shared_ptr<LukkelEngine::Shader> m_Shader;
	std::shared_ptr<LukkelEngine::VertexArray> m_VertexArray;


	LukkelEngine::Camera m_Camera;
}

void TestLayer::onUpdate(float t)
{
	ImGui_ImplGlfwGL3_NewFrame();
	m_Scene->onUpdate();
	onImGuiRender();
}

void TestLayer::onImGuiRender()
{
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate); 
}

void TestLayer::onEvent(LukkelEngine::Event& e)
{

}

void TestLayer::onAttach()
{
	LKLOG_WARN("onAttach() called");
	m_Scene = std::make_shared<LukkelEngine::Scene>();

	LukkelEngine::Entity* Rectangle = new LukkelEngine::Entity;
	LukkelEngine::VertexArray* va = new LukkelEngine::VertexArray();
	LukkelEngine::VertexBuffer* vb = new LukkelEngine::VertexBuffer(rectangle, (sizeof(rectangle) / (sizeof(float)) * sizeof(float)));
	LukkelEngine::IndexBuffer* ib = new LukkelEngine::IndexBuffer(rectangle_indices, (sizeof(rectangle_indices) / sizeof(unsigned int)) * sizeof(unsigned int));
	auto layout = new LukkelEngine::VertexBufferLayout();
	layout->push<float>(2);
	va->addBuffer(*vb, *layout);
	// auto shader = new LukkelEngine::Shader("res/shaders/3D/color3D.shader");
	auto shader = new LukkelEngine::Shader("res/shaders/basic2.shader");
	shader->bind();
	shader->setUniform4f("u_Color", 0.5f, 0.8f, 0.5f, 1.0f);

	Rectangle->setVertexArray(*va);
	Rectangle->setVertexBuffer(*vb);
	Rectangle->setIndexBuffer(*ib);
	Rectangle->setVertexShader(*shader);

	m_Scene->addEntity(*Rectangle);
}

void TestLayer::onDetach()
{

}
