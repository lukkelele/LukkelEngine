#include "LKpch.h"
#include "LukkelEngine/Scene/EntityFactory.h"
#include "LukkelEngine/Renderer/MeshFactory.h"
#include "LukkelEngine/Physics/Body/RigidBodyFactory.h"
#include "LukkelEngine/Physics/World.h"


namespace LukkelEngine {


	void EntityFactory::createBox(EntityProperties props, Scene& scene)
	{
		Entity entity = scene.createEntity(props.name);
		std::string shaderPath = "assets/shaders/flat.shader";
		glm::vec3 inertia(0.0f, 0.0f, 0.0f);
		float restitution = 0.3f;
		float friction = 1.0f;

		Mesh& mesh = MeshFactory::createBox(props.dimensions);
		RigidBody& rigidbody = RigidBodyFactory::createRigidBody(props.dimensions, props.offset, 
									props.mass, props.bodytype, friction, restitution, inertia);
		Material material;
		material.setMaterialColor(props.color);

		entity.addComponent<Mesh>(mesh);
		entity.addComponent<RigidBody>(rigidbody);
		entity.addComponent<Material>(material);
		entity.addComponent<TransformComponent>();
	}

}