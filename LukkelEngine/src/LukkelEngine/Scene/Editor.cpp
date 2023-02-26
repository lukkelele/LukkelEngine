#include "LKpch.h"
#include "LukkelEngine/Scene/Editor.h"

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
		listEntities();
		if (selectedEntity != nullptr)
		{
			RigidBodyComponent& body = selectedEntity->getComponent<RigidBodyComponent>();
			ImGui::Text("Position");
			ImGui::SameLine(); ImGui::SliderFloat3("", &(float)body.pos.getX(), -10.0f, 10.0f);
		}
		ImGui::End();
	}

	/**
	 * @brief List all entites in scene
	*/
	void Editor::listEntities()
	{
		ImGui::SetNextItemOpen(true, ImGuiCond_Once);
		if (ImGui::TreeNode("Scene entities"))
		{
			int idx = -1;
			auto map = m_Scene->m_EntityMap;
			for (auto worldObject : map)
			{
				UUID uuid = worldObject.first;
				Entity entity = m_Scene->getEntityWithUUID(uuid);
				std::string name = entity.getName();
				if (ImGui::Selectable(name.c_str(), selectedName != name))
				{
					selectedEntity = &entity;
					LKLOG_CRITICAL("CLICKED -> {0}", entity.getName());
					LKLOG_TRACE("Selected -> {0}", selectedEntity->getName());
				}
			}
			ImGui::TreePop();
		}
		else
			selectedEntity = nullptr;
	}
	

}