#pragma once
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Scene/Components.h"

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

		template<typename T>
		void displayAddComponentEntry(const std::string& entryName);

	private:
		s_ptr<Scene> m_Scene = nullptr;
		static Entity m_SelectedEntity;

		friend class World;
	};

}