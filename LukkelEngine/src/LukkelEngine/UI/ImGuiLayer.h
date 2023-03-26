#pragma once
#include "LukkelEngine/Core/Layer.h" 

#include "GLFW/glfw3.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/ImGuizmo.h"

namespace LukkelEngine {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer() = default;
		ImGuiLayer(GLFWwindow* window);
		~ImGuiLayer() = default;

		void OnUpdate(float ts);

		void BeginFrame();
		void EndFrame();
		void BeginViewport();
		void EndViewport();

		void SetDarkTheme();
		void SetLightTheme();

	private:
		GLFWwindow* m_WindowContext = nullptr;
	};

}