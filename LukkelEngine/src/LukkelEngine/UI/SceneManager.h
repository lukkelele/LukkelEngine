#pragma once

#include "LukkelEngine/Scene/Scene.h"
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
		void drawObjectNode(WorldObject worldObject);
		void drawComponents(WorldObject worldObject);
		void selectObject(WorldObject& worldObject);

		template<typename T>
		void displayAddComponentEntry(const std::string& entryName);

	private:
		s_ptr<Scene> m_Scene = nullptr;
		static WorldObject m_SelectedObject;
	};

}
