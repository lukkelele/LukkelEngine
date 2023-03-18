#include "LKpch.h"
#include "LukkelEngine/Scene/EntityFactory.h"
#include "LukkelEngine/Renderer/MeshFactory.h"
#include "LukkelEngine/Physics/Body/RigidbodyFactory.h"
#include "LukkelEngine/Physics/World.h"


namespace LukkelEngine {


	void EntityFactory::createBox(EntityProperties props, Scene& scene)
	{
		Entity entity = scene.createEntity(props.name);
		std::string shaderPath = "assets/shaders/flat.shader";
		glm::vec3 inertia(0.0f, 0.0f, 0.0f);
		float restitution = 0.3f;
		float friction = 1.0f;

		UUID& entityID = entity.getUUID();
		Mesh& mesh = MeshFactory::createBox(props.dimensions);
		// Rigidbody& rigidbody = RigidbodyFactory::createRigidbody(props.dimensions, props.offset, 
		// 							props.mass, props.bodytype, friction, restitution, inertia);
		Rigidbody& rigidbody = RigidbodyFactory::createRigidbody(entityID, props.dimensions, props.offset, 
									props.mass, props.bodytype, friction, restitution, inertia);
		Material material;
		material.setMaterialColor(props.color);

		entity.addComponent<Mesh>(mesh);
		entity.addComponent<Rigidbody>(rigidbody);
		entity.addComponent<Material>(material);
		entity.addComponent<TransformComponent>();
	}

}