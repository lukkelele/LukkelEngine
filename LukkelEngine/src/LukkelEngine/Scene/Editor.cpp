#include "LKpch.h"
#include "LukkelEngine/Scene/Editor.h"
#include "LukkelEngine/Scene/ObjectHandler.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


namespace LukkelEngine {

	Editor::Editor(s_ptr<Scene> scene)
		: m_Scene(scene)
	{
	}

	/**
	 * @brief Show the editor menu
	*/
	void Editor::displayMenu()
	{
		ImGui::Begin("Editor menu");

		objectManagementMenu();
		ImGui::Separator();
		listEntities();

		if (selectedEntity)
			inspectEntity(*selectedEntity);

		ImGui::End();
	}

	void Editor::objectManagementMenu()
	{
		int collection[] = { LK_OBJECT_CUBE, LK_OBJECT_FLOOR };
		ImGui::Begin;
		ImGui::PushItemWidth(30);
		ImGui::Text("World objects");
		ImGui::PopItemWidth();

		ImGui::Checkbox("Cube", &addCubeFlag);
		ImGui::Checkbox("Floor", &addFloorFlag);

		ImGui::AlignTextToFramePadding();
		if (ImGui::Button("Add"))
		{
			ObjectHandler::addCube(*m_Scene, "Cube");
		}
		// ImGui::SameLine(); ImGui::Button("Delete");

		ImGui::End;

	}

	/**
	 * @brief List all entites in scene
	*/
	void Editor::listEntities()
	{
		ImGui::SetNextItemOpen(true, ImGuiCond_Once);
		if (ImGui::TreeNode("Scene entities"))
		{
			for (auto& worldObject : m_Scene->m_EntityMap)
			{
				UUID uuid = worldObject.first;
				Entity& entity = m_Scene->getEntityWithUUID(uuid);
				// if (ImGui::Button(entity.getName().c_str()))
				// if (ImGui::Selectable(entity.getName().c_str(), &selectedEntity))
				if (ImGui::Selectable(entity.getName().c_str(), selectedEntity))
				{
					selectedEntity = &entity;
				}
			}

			ImGui::TreePop();
		}
		else // if treenode is to be closed
		{
			selectedEntity = nullptr;
		}
	}

	// FIXME: Fix indentation for property entries
	void Editor::inspectEntity(Entity& entity)
	{
		auto e = entity; // Necessary for rest to work, bugged, sometimes cant refer to passed entity parameter ?
		RigidBodyComponent& body = e.getComponent<RigidBodyComponent>();
		ImGui::Begin;
		// Inspector Title
		ImGui::Separator(); ImGui::Indent(); ImGui::Text("Object properties"); ImGui::Separator();
		// Show selected object name
		ImGui::Text("Selected object: %s", e.getName().c_str());
		// Position
		ImGui::Text("Position");
		ImGui::SameLine(); ImGui::SliderFloat3("", &(float)body.pos.getX(), -10.0f, 10.0f);
		// Scaler
		ImGui::Text("Scale"); ImGui::Indent(); ImGui::Indent(); ImGui::SameLine(); ImGui::Indent();
		ImGui::SliderFloat("", &body.scale, 0.01f, 10.0f);
		// Velocity (if applicable)
		if (body.bodyType == RigidBodyComponent::BodyType::DYNAMIC)
		{
			// Linear, angular and pos is somehow moving eachother, need to fix 
			ImGui::Text("Linear velocity");
			ImGui::SliderFloat3("", &(float)body.linearVelocity.getX(), 0.0f, 70.0f);
			ImGui::Text("Angular velocity");
			ImGui::SliderFloat3("", &(float)body.angularVelocity.getX(), 0.0f, 70.0f);
		}

		ImGui::End;
	}
	

}