#include "LukkelEngine/Layer/MenuLayer.h"

#include "LukkelEngine/Core/Application.h"

namespace LukkelEngine {

	MenuLayer::MenuLayer()
	{
	}

	void MenuLayer::onAttach()
	{
		LKLOG_TRACE("MenuLayer attaching...");

		
	}

	void MenuLayer::onUpdate(float ts)
	{

	}


	void MenuLayer::begin()
	{
		ImGui::NewFrame();
	}

	void MenuLayer::end()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::get();
		float width = (float) app.getViewportWidth();
		float height = (float) app.getViewportHeight();
		io.DisplaySize = ImVec2(width, height);
	}

	void MenuLayer::onImGuiRender()
	{
	}

	void MenuLayer::onEvent(LukkelEngine::Event& e)
	{
	}

	void MenuLayer::onDetach()
	{
	}

}
