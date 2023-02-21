#include "LukkelEngine/Layer/PerformanceLayer.h"


namespace LukkelEngine {

	PerformanceLayer::PerformanceLayer()
		: Layer("Performance Layer")
	{
	}

	void PerformanceLayer::FPS()
	{
		ImGui::Text("Average FPS: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate); 
	}

	void PerformanceLayer::onImGuiRender()
	{
		FPS();
	}

}