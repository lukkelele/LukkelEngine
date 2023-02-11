#pragma once

#include "LukkelEngine.h"

class TestLayer : public LukkelEngine::Layer
{
public:
	TestLayer();
	~TestLayer() = default;

	virtual void onAttach() override;
	virtual void onDetach() override;

	void onUpdate(float t = 0) override;
	virtual void onImGuiRender() override;
	void onEvent(LukkelEngine::Event& e) override;

private:
	LukkelEngine::Camera m_Camera;
	// Shared pointer
	LukkelEngine::s_ptr<LukkelEngine::Scene> m_Scene;
};