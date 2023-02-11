#include "LukkelEngine/Layer/ImGuiLayer.h"

// #include <imgui_impl_opengl3.h>


namespace LukkelEngine {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	void ImGuiLayer::begin()
	{
	}

	void ImGuiLayer::end()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::get();
		float width = (float) app.getViewportWidth();
		float height = (float) app.getViewportHeight();
		io.DisplaySize = ImVec2(width, height);
	}

	void ImGuiLayer::onUpdate()
	{

	}
	void ImGuiLayer::onImGuiRender()
	{
	}

	void ImGuiLayer::onEvent(LukkelEngine::Event& e)
	{

	}

	void ImGuiLayer::onAttach()
	{
		// m_Scene->addEntity(*Rect);
	}

	void ImGuiLayer::onDetach()
	{
		// ImGui_ImplOpenGL3_Shutdown(); // UNRESOLVED EXTERNALS
		// ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

}