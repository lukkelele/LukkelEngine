#pragma once
#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Scene/Entity.h"

namespace LukkelEngine {

	class Scene;

	class EntityFactory
	{
	public:
		EntityFactory() = default;
		~EntityFactory() = default;

		static void createBox(glm::vec3& dims, const std::string& name, Scene& scene);
	};

}