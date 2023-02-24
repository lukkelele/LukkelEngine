#pragma once
#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/Shader.h"
#include "LukkelEngine/Renderer/Texture.h"

#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "glm/glm.hpp"


namespace LukkelEngine{
	
	struct MeshComponent
	{
		s_ptr<VertexArray> va;
		s_ptr<Shader> shader;
		s_ptr<Texture> texture;

		MeshComponent() = default;
		MeshComponent(const MeshComponent&) = default;
		MeshComponent(s_ptr<VertexArray>& va, s_ptr<Shader>& shader, s_ptr<Texture>& texture)
			: va(va), shader(shader), texture(texture) {}

		void bind()
		{
			va->bind();
			shader->bind();
			texture->bind();
		}
	};

	struct TransformComponent
	{
		glm::mat4 transform = glm::mat4(1.0f);
		glm::vec3 translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default; // Copy
		TransformComponent(const glm::mat4& transform)
			: transform(transform) {}

		// This is like an implicit cast which makes so you can skip e.g Component.component
		operator glm::mat4& () { return transform; }
		operator const glm::mat4& () const { return transform; }

		glm::mat4 getTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(rotation));
			// Translation * Rotation * Scale
			return glm::translate(glm::mat4(1.0f), translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), scale);
		}
	};

	struct SpriteRendererComponent
	{
		glm::vec4 color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: color(color) {}
	};

	struct RigidBody3DComponent
	{
		enum class BodyType { STATIC = 0, DYNAMIC, KINEMATIC };

		btCollisionShape* shape = nullptr;
		float friction = 0.50f;
		float restitution = 0.0f;
		btScalar mass = 1.0f;
		btVector3 linearVelocity{ 0.0f, 0.0f, 0.0f };
		btVector3 angularVelocity{ 0.0f, 0.0f, 0.0f };
		btVector3 inertia{ 0.0f, 0.0f, 0.0f };
		btRigidBody* rigidbody = nullptr;
		btDefaultMotionState* motionState = nullptr;

		RigidBody3DComponent() = default;
		RigidBody3DComponent(const RigidBody3DComponent&) = default; // Copy
	};


	template<typename... Component>
	struct ComponentGroup
	{
	};

	using AllComponents =
		ComponentGroup<TransformComponent, SpriteRendererComponent,
					   RigidBody3DComponent>;

}
