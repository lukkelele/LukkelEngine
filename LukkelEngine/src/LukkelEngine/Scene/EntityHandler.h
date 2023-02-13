#pragma once
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Scene/Scene.h"

/* Modify entities in scenes */
namespace LukkelEngine {

	class EntityHandler
	{
	public:

		static void addEntity(Entity& entity, Scene* scene);
		static void removeEntity(Entity& entity);

	};

}