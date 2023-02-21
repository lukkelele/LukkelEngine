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
	float inc = 0.02;

	glm::vec3 colorSlider1 = { 1.0f, 1.0f, 1.0f };
	glm::vec3 colorSlider2 = { 1.0f, 1.0f, 1.0f };
	glm::vec3 sliderBuff2 = { 0.0f, 0.0f, 0.0f };
	glm::vec3 sliderBuff3 = { 0.0f, 0.0f, 0.0f };

private:
	LukkelEngine::s_ptr<LukkelEngine::Scene> m_Scene;
};