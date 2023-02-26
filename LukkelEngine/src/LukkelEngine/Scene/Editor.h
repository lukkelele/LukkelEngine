#pragma once
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Scene/Components.h"
#include "LukkelEngine/Core/Timer.h"
#include "LukkelEngine/Core/UUID.h"

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

		void displayMenu();
		void objectManagementMenu();
		void listEntities();
		void inspectEntity(Entity& entity);

		bool addCubeFlag = false;
		bool addFloorFlag = false;

	public:
		s_ptr<Scene> m_Scene = nullptr;
		Entity* selectedEntity = nullptr;
		int selectedIdx = 0;
	};
}