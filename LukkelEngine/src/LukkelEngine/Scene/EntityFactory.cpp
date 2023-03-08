#include "LKpch.h"
#include "LukkelEngine/Scene/EntityFactory.h"
#include "LukkelEngine/Renderer/MeshFactory.h"
#include "LukkelEngine/Physics/Body/RigidBodyFactory.h"

#include "LukkelEngine/Physics/World.h"


namespace LukkelEngine {


	Entity EntityFactory::createBox(glm::vec3& dims, glm::vec3& offset, const std::string& name, RigidBody::Type bodytype, Scene& scene)
	{
		Entity entity = scene.createEntity(name);
		std::string shaderPath = "assets/shaders/flat.shader";
		glm::vec3 inertia(0.0f, 0.0f, 0.0f);
		float mass = 5.0f;
		float restitution = 0.3f;
		float friction = 1.0f;

		Mesh& mesh = MeshFactory::createBox(dims);
		RigidBody& rigidbody = RigidBodyFactory::createRigidBody(dims, offset, mass, bodytype, friction, restitution, inertia);
		Material material;

		entity.addComponent<Mesh>(mesh);
		entity.addComponent<RigidBody>(rigidbody);
		entity.addComponent<Material>(material);

		// Has to be called here? or else does not apply for some reason
		// rigidbody.setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);

		LKLOG_INFO("Created box: {0}", name);
		return entity;
	}

}