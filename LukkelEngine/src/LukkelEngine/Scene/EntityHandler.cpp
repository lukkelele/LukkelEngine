#include "LukkelEngine/Scene/EntityHandler.h"

namespace LukkelEngine {

	
	void EntityHandler::addEntity(Entity& entity, Scene *scene)
	{
		scene->addEntity(entity);
	}
	
	void EntityHandler::removeEntity(Entity& entity)
	{

	}

}
