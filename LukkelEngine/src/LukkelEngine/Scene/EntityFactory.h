#pragma once
#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Scene/Components.h"

namespace LukkelEngine {

	class Scene;

	namespace EntityProperties {

		struct Cube
		{
			std::string name;
			glm::vec3 dimensions;
			glm::vec3 offset;
			float mass;
			Rigidbody::Type rigidbodyType;
			glm::vec4 color;

			Cube(const std::string& entityName = "Entity",
				Rigidbody::Type rigidbodyType = Rigidbody::Type::STATIC,
				glm::vec3 dims = glm::vec3(1.0f, 1.0f, 1.0f),
				glm::vec3 off = glm::vec3(0.0f, 0.0f, 0.0f),
				float mass = 1.0f,
				glm::vec4 color = Color::White)
				: name(entityName), dimensions(dims), offset(off),
				  mass(mass), rigidbodyType(rigidbodyType), color(color) 
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

			Sphere(const std::string& entityName = "Entity", 
				Rigidbody::Type bodyType = Rigidbody::Type::STATIC, float radius = 1.0f,
				glm::vec3 off = glm::vec3(0.0f, 0.0f, 0.0f), float mass = 1.0f,
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

		static void CreateCube(EntityProperties::Cube props);
		static void CreateSphere(EntityProperties::Sphere props);
	};

}