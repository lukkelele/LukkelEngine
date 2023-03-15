#pragma once

#include "LukkelEngine/Core/Application.h"
#include "LukkelEngine/Editor/EditorLayer.h"

class TestLayer : public LukkelEngine::Layer
{
public:
	TestLayer();
	~TestLayer() = default;

	virtual void onAttach() override;
	virtual void onDetach() override;

	void onUpdate(float ts) override;
	virtual void onImGuiRender() override;
	void onEvent(LukkelEngine::Event& e) override;

	float r = 0.0f;
	float b = 0.5f;
	float inc = 0.02;

private:
	LukkelEngine::s_ptr<LukkelEngine::Scene> m_Scene = nullptr;
	LukkelEngine::s_ptr<LukkelEngine::EditorLayer> m_EditorLayer = nullptr;
};