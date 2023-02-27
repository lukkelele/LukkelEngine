#pragma once
#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/Shader.h"
#include "LukkelEngine/Renderer/Texture.h"
#include "LukkelEngine/Core/UUID.h"

#include "LukkelEngine/Scene/Components/MeshComponent.h"
#include "LukkelEngine/Scene/Components/RigidBodyComponent.h"

#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "glm/glm.hpp"

#define LK_TEMPLATE_OBJECT_CUBE 4
#define LK_TEMPLATE_OBJECT_FLOOR 5


namespace LukkelEngine{

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
	
	struct MeshComponent;
	struct RigidBodyComponent;

	struct SpriteComponent
	{
		glm::vec4 color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteComponent() = default;
		SpriteComponent(const SpriteComponent&) = default;
		SpriteComponent(const glm::vec4& color)
			: color(color) {}
	};



	template<typename... Component>
	struct ComponentGroup
	{
	};

	using AllComponents =
		ComponentGroup<IDComponent,
					   TagComponent,
					   SpriteComponent,
					   RigidBodyComponent>;

}
