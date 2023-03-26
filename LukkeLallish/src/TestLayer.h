#pragma once

#include "LukkelEngine/Core/Application.h"
#include "LukkelEngine/Editor/EditorLayer.h"

class TestLayer : public LukkelEngine::Layer
{
public:
	TestLayer();
	~TestLayer() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(float ts) override;
	void OnImGuiRender() override;
	void OnEvent(LukkelEngine::Event& e) override;

	float r = 0.0f;
	float b = 0.5f;
	float inc = 0.02;

private:
	LukkelEngine::s_ptr<LukkelEngine::Scene> m_Scene = nullptr;
	LukkelEngine::s_ptr<LukkelEngine::EditorLayer> m_EditorLayer = nullptr; // Change to scene
};