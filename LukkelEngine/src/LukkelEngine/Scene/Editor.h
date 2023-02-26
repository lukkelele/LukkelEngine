#pragma once
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Scene/Components.h"
#include "LukkelEngine/Core/Timer.h"
#include "LukkelEngine/Core/UUID.h"

#include "entt/entt.hpp"


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
		void listEntities();


	public:
		s_ptr<Scene> m_Scene = nullptr;
		Entity* selectedEntity = nullptr;
		std::string selectedName = "";
	};
}