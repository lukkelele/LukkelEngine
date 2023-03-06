#pragma once

#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Core/UUID.h"
#include "LukkelEngine/Model/WorldObject.h"

#include "imgui/imgui_internal.h"
#include "entt/entt.hpp"


namespace LukkelEngine {

	class SceneManager
	{
	public:
		SceneManager(Scene& scene);
		~SceneManager() = default;

		void onImGuiRender();
		void drawEntityNode(Entity entity);
		void drawComponents(Entity entity);
		void selectEntity(Entity& entity);

		template<typename T>
		void displayAddComponentEntry(const std::string& entryName);

	private:
		s_ptr<Scene> m_Scene = nullptr;
		static Entity m_SelectedEntity;
	};

}
