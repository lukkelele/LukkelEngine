#pragma once
#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/Shader.h"
#include "LukkelEngine/Renderer/Texture.h"
#include "LukkelEngine/Core/UUID.h"
#include "LukkelEngine/Renderer/Mesh.h"
#include "LukkelEngine/Renderer/Material.h"
#include "LukkelEngine/Physics/Body/RigidBody.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>


namespace LukkelEngine{

	class Material;
	class Mesh;
	class RigidBody;

	struct IDComponent
	{
		UUID ID;

		IDComponent() = default;
		IDComponent(const IDComponent&) = default;
	};

	struct TagComponent
	{
		std::string tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: tag(tag) {}
	};

	struct TransformComponent
	{
		glm::vec3 translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
		glm::quat rotation = { 1.0f, 0.0f, 0.0f, 0.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = default;
		TransformComponent(const glm::vec3& translation)
			: translation(translation) {}

		glm::mat4 getTransform() const
		{
			return glm::translate(glm::mat4(1.0f), translation)
				 * glm::toMat4(rotation)
				 * glm::scale(glm::mat4(1.0f), scale);
		}

	};


	template<typename... Component>
	struct ComponentGroup
	{
	};

	using AllComponents =
		ComponentGroup<IDComponent, TagComponent, Mesh, RigidBody>;

}
