#pragma once

#include "LukkelEngine.h"

class TestLayer : public LukkelEngine::Layer
{
public:
	TestLayer();
	virtual ~TestLayer() = default;

	virtual void onAttach() override;
	virtual void onDetach() override;

	void onUpdate(float t = 0) override;
	virtual void onImGuiRender() override;
	void onEvent(LukkelEngine::Event& e) override;

private:
	LukkelEngine::s_ptr<LukkelEngine::Shader> m_Shader;
	LukkelEngine::s_ptr<LukkelEngine::VertexArray> m_VertexArray;

	LukkelEngine::s_ptr<LukkelEngine::Shader> m_FlatColorShader;
	LukkelEngine::s_ptr<LukkelEngine::VertexArray> m_SquareVA;


	LukkelEngine::Camera m_Camera;
};