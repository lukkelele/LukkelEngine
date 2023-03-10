#pragma once
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Scene/Components.h"
#include "LukkelEngine/Renderer/Mesh.h"
#include "LukkelEngine/Physics/Body/RigidBody.h"
#include "LukkelEngine/Renderer/Material.h"

#include "imgui/imgui_internal.h"
#include "entt/entt.hpp"

namespace LukkelEngine {

	enum LK_OBJECT
	{
		LINE, CUBE, SPHERE
	};

	class Editor
	{
	public:
		Editor(s_ptr<Scene> scene);
		~Editor() = default;

		void createEntity(unsigned int entityType, std::string_view objectName = "");
		void addEntity(Entity& entity);

		void onImGuiRender();
		void drawEntityNode(Entity entity);
		void drawComponents(Entity entity);
		void selectEntity(Entity& entity);

		static void drawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f);
		static void drawVec4Control(const std::string& label, glm::vec4& values, float min = 0.0f, float max = 1.0f, float resetValue = 0.0f, float columnWidth = 100.0f);

		template<typename T, typename UIFunction>
		static void drawComponent(const std::string& name, Entity entity, UIFunction uiFunction);

		template<typename T>
		void displayAddComponentEntry(const std::string& entryName);

	private:
		s_ptr<Scene> m_Scene = nullptr;
		static Entity m_SelectedEntity;

		friend class World;
	};

}