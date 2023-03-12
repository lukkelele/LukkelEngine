#include "LKpch.h"
#include "LukkelEngine/Editor/Editor.h"
#include "LukkelEngine/Physics/World.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_internal.h"


namespace LukkelEngine {

	Entity Editor::m_SelectedEntity;

	Editor::Editor(s_ptr<Scene> scene)
		: m_Scene(scene)
	{
	}

	void Editor::createEntity(unsigned int objectType, std::string_view objectName)
	{

	}

	void Editor::addEntity(Entity& entity)
	{

	}

	void Editor::onImGuiRender()
	{
		ImGui::Begin("Editor menu");

		if (m_Scene)
		{
			m_Scene->m_Registry.each([&](auto entityID)
			{
				Entity entity{ entityID, m_Scene.get() };
				drawEntityNode(entity);
			});

			if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
				m_SelectedEntity = {};

			// Right click on blank space to get popup menu
			if (ImGui::BeginPopupContextWindow(0, 1, false)) // id, mouse button, if on item (bool)
			{
				// if (ImGui::MenuItem("New entity"))
				// 	m_Scene->createEntity("Empty Entity");

				// else if (ImGui::MenuItem("New Cube"))
				// 	// Spawner::createCube(*m_Scene, "Cube");
				// 	void;

				// else if (ImGui::MenuItem("New floor (ground object)"))
				// 	void;
				// 	// Spawner::createGround(*m_Scene, "Floor");

				ImGui::EndPopup();
			}
		}

		ImGui::Begin("Properties");
		if (m_SelectedEntity)
		{
			drawComponents(m_SelectedEntity);
		}
		ImGui::End();

		ImGui::End();
	}

	void Editor::selectEntity(Entity& entity)
	{
		if (m_SelectedEntity != entity)
			m_SelectedEntity = entity;
	}

	void Editor::drawEntityNode(Entity entity)
	{
		auto& tag = entity.getComponent<TagComponent>().tag;

		ImGuiTreeNodeFlags flags = ((m_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectedEntity = entity;
		}

		bool entityDeleted = false;
		bool entityReset = false;

		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete object"))
				entityDeleted= true;
			else if (ImGui::MenuItem("Reset object"))
				entityReset = true;

			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		}

		if (entityDeleted)
		{
			m_Scene->destroyEntity(entity);
				if (m_SelectedEntity == entity)
					m_SelectedEntity = {};
			LKLOG_ERROR("Entity deleted (EDITOR)");
		}
	}

	template<typename T, typename UIFunction>
	void Editor::drawComponent(const std::string& name, Entity entity, UIFunction uiFunction)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
		if (entity.hasComponent<T>())
		{
			auto& component = entity.getComponent<T>();
			ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str());
			ImGui::PopStyleVar(
			);
			ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
			if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}

			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove component"))
					removeComponent = true;

				ImGui::EndPopup();
			}

			if (open)
			{
				uiFunction(component);
				ImGui::TreePop();
			}

			if (removeComponent)
				entity.removeComponent<T>();
		}
	}

	template<typename T>
	void Editor::displayAddComponentEntry(const std::string& entryName)
	{
		if (!m_SelectedEntity.hasComponent<T>())
		{
			if (ImGui::MenuItem(entryName.c_str()))
			{
				m_SelectedEntity.addComponent<T>();
				ImGui::CloseCurrentPopup();
			}
		}
	}

	void Editor::drawComponents(Entity entity)
	{
		if (entity.hasComponent<TagComponent>())
		{
			auto& tag = entity.getComponent<TagComponent>().tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			std::strncpy(buffer, tag.c_str(), sizeof(buffer));
			if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);

		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("AddComponent");

		if (ImGui::BeginPopup("AddComponent"))
		{
			displayAddComponentEntry<Mesh>("Mesh");
			displayAddComponentEntry<RigidBody>("Rigidbody");
			displayAddComponentEntry<Material>("Material");
			ImGui::EndPopup();
		}

		ImGui::PopItemWidth();

		drawComponent<Mesh>("Mesh", entity, [](auto& component)
		{

		});

		drawComponent<TransformComponent>("Transform", entity, [](auto& component)
		{
			/* Translation / Position */
			glm::vec3 translation = component.translation;
			UI::Property::vec3Control("Position", translation);
			component.translation = translation;
			/* Scale */
			glm::vec3 scale = component.scale;
			UI::Property::vec3Control("Scale", scale);
		});

		// TODO: Selected entities shall have their (if body exists) body put under a constraint
		drawComponent<RigidBody>("Rigidbody", entity, [](auto& component)
		{
			/* Display menu for manipulating body properties */
			glm::vec3 linearVelocity = component.getLinearVelocity();
			glm::vec3 oldLinearVelocity = linearVelocity;
			UI::Property::vec3Control("Linear Velocity", linearVelocity);
		});

		drawComponent<Material>("Material", entity, [](auto& component)
		{
			/* Display color menu for the entity*/
			UI::Property::colorMenu(component);
		});

	}

}