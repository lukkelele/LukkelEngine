#pragma once

#include "LukkelEngine.h"
#include "LukkelEngine/Input/Keyboard.h"

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

	// TESTING ONLY
	float r = 0.0f;
	float b = 0.5f;

private:
	// Shared pointer
	LukkelEngine::s_ptr<LukkelEngine::Scene> m_Scene;
};