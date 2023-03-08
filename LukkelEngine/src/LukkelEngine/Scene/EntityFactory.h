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

		static Entity createBox(glm::vec3& dims, glm::vec3& offset, const std::string& name, RigidBody::Type bodytype, Scene& scene);
	};

}