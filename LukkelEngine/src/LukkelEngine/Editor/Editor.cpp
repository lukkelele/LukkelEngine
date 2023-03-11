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

	void Editor::drawVec3Control(const std::string& label, glm::vec3& values, float resetValue, float columnWidth)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();
		ImGui::Columns(1);
		ImGui::PopID();
	}

	void Editor::drawVec4Control(const std::string& label, glm::vec4& values, float min, float max, float resetValue, float columnWidth)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];
		float speed = 0.01f;

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(4, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		/* X SLIDER */
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, speed, min, max, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		/* Y SLIDER */
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, speed, min, max, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		/* Z SLIDER */
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, speed, min, max, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.33f, 0.33f, 0.33f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		/* W SLIDER */
		if (ImGui::Button("W", buttonSize))
			values.w = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##W", &values.w, speed, min, max, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();
		ImGui::Columns(1);
		ImGui::PopID();
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
			drawVec3Control("Position", translation);
			component.translation = translation;
			/* Scale */
			glm::vec3 scale = component.scale;
			drawVec3Control("Scale", scale);
		});

		drawComponent<RigidBody>("Rigidbody", entity, [](auto& component)
		{

		});

		drawComponent<Material>("Material", entity, [](auto& component)
		{
			glm::vec4 color = component.getMaterialColor();
			drawVec4Control("Color", color);
			glm::vec4 newColor = { color.x, color.y, color.z, color.w };
			component.setMaterialColor(newColor);

			ImGui::Separator();
			float columnSize = 100.0f;
			ImGuiIO& io = ImGui::GetIO();
			auto boldFont = io.Fonts->Fonts[0];
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImVec2 listBoxSize = { columnSize , lineHeight * 5 };
			ImVec2 buttonSize = { lineHeight + 20.0f, lineHeight };

			static std::vector<std::pair<std::string, glm::vec4>> colors;
			static std::pair ColorBlack = std::make_pair("Black", Color::Black); 
			static std::pair ColorWhite = std::make_pair("White", Color::White);
			static std::pair ColorCyan = std::make_pair("Cyan", Color::Cyan);
			static std::pair ColorSilver = std::make_pair("Silver", Color::Silver);
			static std::pair ColorRed = std::make_pair("Red", Color::Red);
			static std::pair ColorMagenta = std::make_pair("Magenta", Color::Magenta);
			static std::pair ColorYellow = std::make_pair("Yellow", Color::Yellow);
			static uint8_t colorsArraySize = 7;
			colors.resize(colorsArraySize);
			colors[0] = ColorBlack;
			colors[1] = ColorWhite;
			colors[2] = ColorCyan;
			colors[3] = ColorSilver;
			colors[4] = ColorRed;
			colors[5] = ColorYellow;
			colors[6] = ColorMagenta;

			static int currentItemIndex = 0;
			auto currentColor = color;

			std::string title = "Colors";
			float columnWidth = 100.0f;

			ImGui::PushID(title.c_str());
			ImGui::Text(title.c_str());
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
			ImGui::ListBoxHeader("", listBoxSize);
			for (int i = 0; i < colorsArraySize; i++)
			{
				const bool isSelected = (currentItemIndex == i);
				if (ImGui::Selectable(colors[i].first.c_str(), isSelected))
					currentItemIndex = i;

				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
					auto colorPair = colors[currentItemIndex];
					auto materialColor = component.getMaterialColor();
					if (materialColor != colorPair.second)
						currentColor = colorPair.second;
				}
			}
			ImGui::ListBoxFooter();
			ImGui::NextColumn();
			ImGui::PushFont(boldFont);
			if (ImGui::Button("Apply", buttonSize))
				component.setMaterialColor(currentColor);
			ImGui::PopFont();
			ImGui::PopStyleColor(1);
			ImGui::PopID();
		});

	}

}