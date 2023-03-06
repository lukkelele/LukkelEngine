#pragma once
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Model/WorldObject.h"

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

		void onImGuiRender();

		void drawEntityNode(Entity entity);
		void drawComponents(Entity entity);

		void createWorldObject(unsigned int objectType, std::string_view objectName = "");
		void addObject(WorldObject& worldObject);
		void selectEntity(Entity& entity);


	private:
		s_ptr<Scene> m_Scene = nullptr;

		friend class World;
	};

}