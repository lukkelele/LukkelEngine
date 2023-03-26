#pragma once
#include "LukkelEngine/Physics/Rigidbody.h"
#include "LukkelEngine/Physics/Constraints.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_internal.h>
#include <format>


namespace LukkelEngine::UI {

	static enum class Dir
	{
		UP = ImGuiDir_Up,
		LEFT = ImGuiDir_Left,
		RIGHT = ImGuiDir_Right,
		DOWN = ImGuiDir_Down
	};

	void static MainMenu() 
	{
		ImGui::BeginMainMenuBar();

		ImGui::EndMainMenuBar();
	}

	void static SideBar(Dir direction, float width)
	{
        ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGuiWindowFlags sideBarFlags = ImGuiWindowFlags_NoMove;

		char barID[20];
		sprintf(barID, "SideBar%d", (int)direction);
		ImGui::BeginViewportSideBar(barID, viewport, (int)direction, width, sideBarFlags);

		ImGuiID dockspaceID = ImGui::GetID(barID);
		static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;
		ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);


		ImGui::BeginChild("Container", ImVec2(0, 0), false);
		ImGui::EndChild();

		ImGui::End();
	}


	static void ConstraintsMenu(Rigidbody& rigidbody)
	{
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImGui::Separator();

		// if (ImGui::Button("Add", ImVec2{ lineHeight, lineHeight }))
		static ImGuiTableFlags constraintFlags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg 
			| ImGuiTableFlags_Borders | ImGuiTableFlags_SizingStretchSame;

		ImGui::Text("Constraints");
		if (ImGui::BeginTable("Constraints", 2, constraintFlags))
		{
			// Column 0
			auto constraints = rigidbody.GetConstraints();
			uint16_t placedConstraints = constraints.size();

			ImGui::TableSetupColumn("Add", ImGuiTableColumnFlags_WidthFixed, 100.0f);
			ImGui::TableSetupColumn("Placed", ImGuiTableColumnFlags_WidthFixed, 216.0f);
			ImGui::TableHeadersRow();
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);

			// Buttons for different types of constraints
			if (ImGui::Button("Pivot", ImVec2{ 0, 0 }))
				rigidbody.AddPivotConstraint(glm::vec3(0.5f, 0.5f, 0.0f));

			if (ImGui::Button("Hinge", ImVec2{ 0, 0 }))
				LKLOG_TRACE("Clicked HINGE button");
			
			if (ImGui::Button("Dof6", ImVec2{ 0, 0 }))
				rigidbody.AddDof6Constraint(glm::vec3(0.5f, 0.5f, 0.0f));


			// Column 1
			// Placed Constraints
			ImGui::TableSetColumnIndex(1);
			ImGui::Text("Total: %d", placedConstraints);

			uint8_t idx = 0;
			for (auto& constraint : constraints)
			{
				char sbuf[40];
				sprintf(sbuf, "DELETE %s ##%d", constraint->GetName(), idx);
				if (ImGui::Button(sbuf, ImVec2{ 0, 0 }))
					rigidbody.RemoveConstraint(constraint);
				idx++;
			}

			ImGui::EndTable();
		}

	}


}