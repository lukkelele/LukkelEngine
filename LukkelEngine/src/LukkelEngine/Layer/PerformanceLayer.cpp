#include "LKpch.h"
#include "LukkelEngine/Layer/PerformanceLayer.h"

#include "LukkelEngine/Core/Application.h" // FIXME: Fix better getters for camera etc

namespace LukkelEngine {

	PerformanceLayer::PerformanceLayer()
		: Layer("PerformanceLayer")
	{
	}

	void PerformanceLayer::onUpdate(float ts)
	{
	}

	void PerformanceLayer::FPS()
	{
		ImGui::Text("Average FPS: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate); 
	}

	void PerformanceLayer::onImGuiRender()
	{
		auto cam = Application::get().getScene()->getCamera();
		ImGui::Begin("Performance");
		FPS();
		ImGui::End();
	}

}