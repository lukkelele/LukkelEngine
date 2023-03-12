#pragma once
#include "LukkelEngine/Core/Layer.h" 

#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace LukkelEngine {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		ImGuiLayer(GLFWwindow* window);
		~ImGuiLayer() = default;

		void onUpdate(float ts);

		void onAttach();
		void onDetach();

		void setDarkTheme();
		void setLightTheme();

	private:
		GLFWwindow* m_WindowContext = nullptr;
	};

}