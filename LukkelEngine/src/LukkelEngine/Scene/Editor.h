#pragma once
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Core/Timer.h"
#include "LukkelEngine/Core/UUID.h"
#include "LukkelEngine/Renderer/Mesh.h"
#include "LukkelEngine/Renderer/RigidBody.h"

#include "imgui/imgui_internal.h"
#include "entt/entt.hpp"

#define LK_OBJECT_CUBE 10
#define LK_OBJECT_FLOOR 11

namespace LukkelEngine {

	/**
	 * @brief Level editor
	*/
	class Editor
	{
	public:
		Editor(s_ptr<Scene> scene);
		~Editor() = default;

		void onImGuiRender();
		void objectManagementMenu();

		void drawEntityNode(Entity entity);
		void drawComponents(Entity entity);

		template<typename T>
		void displayAddComponentEntry(const std::string& entryName);


	public:
		s_ptr<Scene> m_Scene = nullptr;
		Entity m_SelectedEntity;
		int selectedIdx = 0;
	};
}