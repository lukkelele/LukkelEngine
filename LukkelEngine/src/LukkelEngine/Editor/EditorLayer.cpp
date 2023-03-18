#include "LKpch.h"
#include "LukkelEngine/Editor/EditorLayer.h"
#include "LukkelEngine/Physics/World.h"
#include "LukkelEngine/Math/Math.h"
#include "LukkelEngine/Physics/Body/Constraints.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/ImGuizmo.h>


namespace LukkelEngine {

	Entity EditorLayer::m_SelectedEntity;

	EditorLayer::EditorLayer(s_ptr<Scene> scene)
		: m_Scene(scene)
	{
	}

	void EditorLayer::onImGuiRender()
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
			// if (ImGui::BeginPopupContextWindow(0, 1, false)) // id, mouse button, if on item (bool)
			// {
			// 	// if (ImGui::MenuItem("New entity"))
			// 	// 	m_Scene->createEntity("Empty Entity");
			// 	// else if (ImGui::MenuItem("New Cube"))
			// 	// 	// Spawner::createCube(*m_Scene, "Cube");
			// 	// 	void;
			// 	// else if (ImGui::MenuItem("New floor (ground object)"))
			// 	// 	void;
			// 	// 	// Spawner::createGround(*m_Scene, "Floor");
			// 	ImGui::EndPopup();
			// }
		}

		ImGui::Begin("Properties");
		if (m_SelectedEntity)
		{
			drawComponents(m_SelectedEntity);
		}
		ImGui::End(); // Properties

		ImGuiTreeNodeFlags gizmoFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
		ImVec2 buttonSize(76.0f, 30.0f);

		ImGui::Begin("Gizmo", nullptr, gizmoFlags);
		{
			if (ImGui::Button("Translate", buttonSize))
				m_GizmoType = GizmoType::TRANSLATE;
			ImGui::SameLine();
			if (ImGui::Button("Scale", buttonSize))
				m_GizmoType = GizmoType::SCALE;
			ImGui::SameLine();
			if (ImGui::Button("Rotate", buttonSize))
				m_GizmoType = GizmoType::ROTATE;
		}
		ImGui::End();

		ImGui::End(); // Editor Menu

		if (m_SelectedEntity && m_GizmoType != -1)
		{
			auto window = ImGui::GetCurrentWindow();
			ImGui::SetNextWindowViewport(window->ID);
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();
			float windowWidth = (float)ImGui::GetWindowWidth();
			float windowHeight = (float)ImGui::GetWindowHeight();
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

			// This should get the current primary camera, use this for now
			auto camera = m_Scene->getCamera();
			// Get camera view by inversing the camera transform
			glm::mat4 cameraView = camera->getView();
			glm::mat4 cameraProj = camera->getProjection();

			TransformComponent& tc = m_SelectedEntity.getComponent<TransformComponent>();
			RigidBody& rb = m_SelectedEntity.getComponent<RigidBody>();
			glm::mat4 transform = tc.getTransform();

			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProj), 
				(ImGuizmo::OPERATION)m_GizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform));

			if (ImGuizmo::IsUsing())
			{
				glm::vec3 translation, scale;
				glm::quat rotation;
				Math::decomposeTransform(transform, translation, rotation, scale);

				tc.translation = translation;
				tc.rotation = rotation;
				tc.scale = scale;
				// Needs to be synced as the body is constantly affected by its environment
				rb.moveBody(translation);
			}
		}
	}

	void EditorLayer::selectEntity(Entity& entity)
	{
		if (m_SelectedEntity != entity)
			m_SelectedEntity = entity;
	}

	void EditorLayer::drawEntityNode(Entity entity)
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
		}

	}

	template<typename T, typename UIFunction>
	void EditorLayer::drawComponent(const std::string& name, Entity entity, UIFunction uiFunction)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen 
			| ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth
			| ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

		if (entity.hasComponent<T>())
		{
			auto& component = entity.getComponent<T>();
			ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str());
			ImGui::PopStyleVar();
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
	void EditorLayer::displayAddComponentEntry(const std::string& entryName)
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

	void EditorLayer::drawComponents(Entity entity)
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

		drawComponent<TransformComponent>("Transform", entity, [&entity](auto& component)
		{
			/* Translation / Position */
			glm::vec3 translation = component.translation;
			UI::Property::Vector3Control("Position", translation);
			component.translation = translation;

			/* Scale */
			glm::vec3 scale = component.scale;
			UI::Property::Vector3Control("Scale", scale);
			component.scale = scale;
		});

		// TODO: Selected entities shall have their (if body exists) body put under a constraint
		drawComponent<RigidBody>("Rigidbody", entity, [](auto& component)
		{
			glm::vec3 lv = component.getLinearVelocity();
		UI::Property::Vector3Control("Linear Velocity", lv);
		if (btVector3(lv.x, lv.y, lv.z) != component.m_LinearVelocity)
			component.setLinearVelocity(lv);

		if (ImGui::Checkbox("Use physics", &m_SelectedEntity.usePhysics)) {}

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImGui::Separator();

		// if (ImGui::Button("Add", ImVec2{ lineHeight, lineHeight }))
		static ImGuiTableFlags constraintFlags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg 
			| ImGuiTableFlags_Borders | ImGuiTableFlags_SizingStretchSame;

		ImGui::Text("Constraints");
		if (ImGui::BeginTable("Constraints", 2, constraintFlags))
		{
			// Column 0
			uint8_t placedConstraints = component.getConstraints().size();
			ImGui::TableSetupColumn("Add", ImGuiTableColumnFlags_WidthFixed, 100.0f);
			ImGui::TableSetupColumn("Placed", ImGuiTableColumnFlags_WidthFixed, 100.0f);
			ImGui::TableHeadersRow();
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			if (ImGui::Button("Pivot", ImVec2{ 0, 0 }))
			{
				// The pivot should be inside the object, e.g for a cube it is: side / 2
				component.addPivotConstraint(glm::vec3(0.5f, 0.5f, 0.0f));
			}
			// Column 1
			// ImGui::TableSetColumnIndex(1);
			if (ImGui::Button("Hinge", ImVec2{ 0, 0 }))
			{
				LKLOG_TRACE("ADDED HINGE");
			}

			// Placed Constraints
			ImGui::TableSetColumnIndex(1);
			ImGui::Text("Total: %d", placedConstraints);
			if (ImGui::Button("Remove constraint", ImVec2{ 0, 0 }))
			{
				// The pivot should be inside the object, e.g for a cube it is: side / 2
				LKLOG_WARN("Clicked removed constraint button");
				component.removeConstraint(ConstraintType::Pivot);
			}

			ImGui::EndTable();
		}


		});

		drawComponent<Material>("Material", entity, [](auto& component)
		{
			UI::Property::ColorMenu(component);
		});


	}

}