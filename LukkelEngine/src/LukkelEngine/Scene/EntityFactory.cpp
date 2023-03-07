#include "LKpch.h"
#include "LukkelEngine/Scene/EntityFactory.h"
#include "LukkelEngine/Renderer/MeshFactory.h"
#include "LukkelEngine/Physics/Body/RigidBodyFactory.h"

#include "LukkelEngine/Physics/World.h"


namespace LukkelEngine {


	void EntityFactory::createBox(glm::vec3& dims, const std::string& name, Scene& scene)
	{
		Entity entity = scene.createEntity(name);
		std::string shaderPath = "assets/shaders/flat.shader";
		glm::vec3 offset(0.0f, 6.0f, 0.0f);
		glm::vec3 inertia(0.0f, 0.0f, 0.0f);
		float mass = 5.0f;
		float restitution = 0.3f;
		float friction = 1.0f;
		RigidBody::Type bodyType = RigidBody::Type::DYNAMIC;

		// Use same dimensions as mesh box, will implement different functionality to vary this later
		s_ptr<Mesh> mesh = create_s_ptr<Mesh>(MeshFactory::createBox(dims));
		s_ptr<RigidBody> rigidbody = create_s_ptr<RigidBody>(RigidBodyFactory::createRigidBody(dims, offset, mass, bodyType, friction, restitution, inertia));
		s_ptr<Material> debugMaterial = create_s_ptr<Material>(Material::create());

		entity.setMesh(mesh);
		entity.setRigidBody(rigidbody);
		entity.setMaterial(debugMaterial);
		LKLOG_INFO("Created box -> {0}", name);
		// Temporary
		scene.m_Entities.push_back(entity);
		// scene.m_World->addRigidBodyToWorld(rigidbody->getRig);
	}

}