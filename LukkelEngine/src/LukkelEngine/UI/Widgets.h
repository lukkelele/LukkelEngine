#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_internal.h"


namespace LukkelEngine::UI {

	enum class Dir
	{
		UP = ImGuiDir_Up,
		LEFT = ImGuiDir_Left,
		RIGHT = ImGuiDir_Right,
		DOWN = ImGuiDir_Down
	};

	void MainMenu() 
	{
		// ImGui::BeginMainMenuBar();
		// ImGui::EndMainMenuBar();
	}

	void SideBar(Dir direction, float width)
	{
        ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGuiWindowFlags sideBarFlags = ImGuiWindowFlags_NoMove;

		char barID[20];
		sprintf(barID, "SideBar%d", (int)direction);
		ImGui::BeginViewportSideBar(barID, viewport, (int)direction, width, sideBarFlags);

		ImGuiID dockspaceID = ImGui::GetID(barID);
		static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;
		ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);

		ImGui::End();
	}

}