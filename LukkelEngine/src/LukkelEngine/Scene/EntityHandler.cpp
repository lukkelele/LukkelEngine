#include "LKpch.h"
#include "LukkelEngine/Scene/EntityHandler.h"

#include "LukkelEngine/Core/Application.h"

namespace LukkelEngine {

	static void addEntity(Entity& entity);

	void EntityHandler::addEntity(Entity& entity)
	{
		auto scene = Application::get().getScene();
		scene->addEntity(entity);
	}
}