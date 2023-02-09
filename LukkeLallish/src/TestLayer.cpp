#include "TestLayer.h"


TestLayer::TestLayer()
	: Layer("TestLayer")
{
	std::shared_ptr<LukkelEngine::Shader> m_Shader;
	std::shared_ptr<LukkelEngine::VertexArray> m_VertexArray;

	LukkelEngine::Camera m_Camera;

}

void TestLayer::onUpdate(float t)
{

}

void TestLayer::onImGuiRender()
{

}

void TestLayer::onEvent(LukkelEngine::Event& e)
{

}

void TestLayer::onAttach()
{
	LKLOG_WARN("onAttach()!");

}

void TestLayer::onDetach()
{
	LKLOG_WARN("onDetach()");
}
