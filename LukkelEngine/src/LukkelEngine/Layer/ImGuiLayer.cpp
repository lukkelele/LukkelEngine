#include "LukkelEngine/Layer/ImGuiLayer.h"


namespace LukkelEngine {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	void ImGuiLayer::onAttach()
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		/* Enable keyboard */
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui::StyleColorsDark();
		Application& app = Application::get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.getWindow());
	}

	void ImGuiLayer::onUpdate(float ts)
	{

	}

	void ImGuiLayer::begin()
	{
		ImGui::NewFrame();
	}

	void ImGuiLayer::end()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::get();
		float width = (float) app.getViewportWidth();
		float height = (float) app.getViewportHeight();
		io.DisplaySize = ImVec2(width, height);
	}

	void ImGuiLayer::onImGuiRender()
	{
		ImGui::InputText("string", m_Buffer, IM_ARRAYSIZE(m_Buffer));
	}

	void ImGuiLayer::onEvent(LukkelEngine::Event& e)
	{

	}

	void ImGuiLayer::onDetach()
	{
		ImGui::DestroyContext();
	}

}