#pragma once
#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Scene/Components.h"

namespace LukkelEngine {

	class Scene;

	namespace EntityProperties {

		struct Box
		{
			std::string name;
			glm::vec3 dimensions;
			glm::vec3 offset;
			float mass;
			Rigidbody::Type bodytype;
			glm::vec4 color;

			Box(const std::string& entityName = "Entity",
				glm::vec3 dims = glm::vec3(1.0f, 1.0f, 1.0f),
				glm::vec3 off = glm::vec3(0.0f, 0.0f, 0.0f),
				float mass = 1.0f,
				Rigidbody::Type bodyType = Rigidbody::Type::STATIC,
				glm::vec4 color = Color::White)
				: name(entityName), dimensions(dims), offset(off),
				  mass(mass), bodytype(bodyType), color(color) 
			{}
		};

		struct Sphere
		{
			std::string name;
			float radius;
			glm::vec3 offset;
			float mass;
			Rigidbody::Type bodytype;
			glm::vec4 color;

			Sphere(const std::string& entityName = "Entity", float radius = 1.0f,
				glm::vec3 off = glm::vec3(0.0f, 0.0f, 0.0f), float mass = 1.0f,
				Rigidbody::Type bodyType = Rigidbody::Type::STATIC,
				glm::vec4 color = Color::White)
				: name(entityName), radius(radius), offset(off),
				  mass(mass), bodytype(bodyType), color(color) 
			{}
		};
	}

	class EntityFactory
	{
	public:
		EntityFactory() = default;
		~EntityFactory() = default;

		// static Entity createBox(glm::vec3& dims, glm::vec3& offset, const std::string& name, Rigidbody::Type bodytype, Scene& scene);
		static void createBox(EntityProperties::Box props, Scene& scene);
		static void createSphere(EntityProperties::Sphere props, Scene& scene);
	};

}