#include "LKpch.h"
#include "LukkelEngine/Scene/EntityFactory.h"
#include "LukkelEngine/Renderer/MeshFactory.h"
#include "LukkelEngine/Physics/Body/RigidbodyFactory.h"
#include "LukkelEngine/Physics/World.h"


namespace LukkelEngine {


	void EntityFactory::CreateCube(EntityProperties::Cube props)
	{
		auto scene = Scene::GetActiveScene();
		Entity entity = scene->CreateEntity(props.name);
		std::string shaderPath = "assets/shaders/flat.shader";
		glm::vec3 inertia(0.0f, 0.0f, 0.0f);
		float restitution = 0.3f;
		float friction = 1.0f;

		UUID& entityID = entity.getUUID();
		Mesh& mesh = MeshFactory::CreateCube(props.dimensions);
		Rigidbody& rigidbody = RigidbodyFactory::createRigidbody(entityID, Rigidbody::Shape::Cube, props.bodytype, props.dimensions, props.offset, 
											props.mass, friction, restitution, inertia);

		Material material;
		material.SetMaterialColor(props.color);

		entity.AddComponent<Mesh>(mesh);
		entity.AddComponent<Rigidbody>(rigidbody);
		entity.AddComponent<Material>(material);
		entity.AddComponent<TransformComponent>();
	}

	void EntityFactory::CreateSphere(EntityProperties::Sphere props)
	{
		auto scene = Scene::GetActiveScene();
		Entity entity = scene->CreateEntity(props.name);
		std::string shaderPath = "assets/shaders/flat.shader";
		glm::vec3 inertia(0.0f, 0.0f, 0.0f);
		float restitution = 0.3f;
		float friction = 1.0f;

		// UUID& entityID = entity.getUUID();
		// Mesh& mesh = MeshFactory::CreateSphere(props.radius);
		// Rigidbody& rigidbody = RigidbodyFactory::createRigidbody(entityID, props.dimensions, props.offset, 
		// 									  props.mass, props.bodytype, friction, restitution, inertia);

		// Material material;
		// material.setMaterialColor(props.color);

		// entity.AddComponent<Mesh>(mesh);
		// entity.AddComponent<Rigidbody>(rigidbody);
		// entity.AddComponent<Material>(material);
		// entity.AddComponent<TransformComponent>();
	}


}