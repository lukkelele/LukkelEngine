#pragma once
#include "LukkelEngine/Physics/Body/RigidBody.h"
#include "LukkelEngine/Physics/Body/Constraints.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_internal.h>


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


	static void ConstraintsMenu(RigidBody& rigidbody)
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
			uint8_t placedConstraints = rigidbody.getConstraints().size();
			ImGui::TableSetupColumn("Add", ImGuiTableColumnFlags_WidthFixed, 100.0f);
			ImGui::TableSetupColumn("Placed", ImGuiTableColumnFlags_WidthFixed, 100.0f);
			ImGui::TableHeadersRow();
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			if (ImGui::Button("Pivot", ImVec2{ 0, 0 }))
			{
				rigidbody.addPivotConstraint(glm::vec3(0.5f, 0.5f, 0.0f));
			}
			// Column 1
			// ImGui::TableSetColumnIndex(1);
			if (ImGui::Button("Hinge", ImVec2{ 0, 0 }))
			{
				LKLOG_TRACE("Clicked HINGE button");
			}

			// Placed Constraints
			ImGui::TableSetColumnIndex(1);
			ImGui::Text("Total: %d", placedConstraints);
			if (ImGui::Button("Remove constraint", ImVec2{ 0, 0 }))
			{
				// The pivot should be inside the object, e.g for a cube it is: side / 2
				rigidbody.removeConstraint(ConstraintType::Pivot);
			}
			ImGui::EndTable();
		}


	}


}