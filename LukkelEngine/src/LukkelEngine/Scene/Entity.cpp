#include "LKpch.h"
#include "LukkelEngine/Scene/Entity.h"


namespace LukkelEngine {


	 Entity::Entity(entt::entity handle, Scene* scene)
	 	: m_EntityHandle(handle), m_Scene(scene)
	 {
	 }

	void Entity::onUpdate(float ts, glm::mat4 viewProj)
	{
		// Get updates from rigidbody
		if (hasComponent<RigidBody>())
		{
			// if the entity has a rigidbody, sync the body with the transform component
			RigidBody& rigidbody = getComponent<RigidBody>();
			auto [pos, rot] = rigidbody.getPosAndRotation();
			glm::vec3 dimensions = rigidbody.getDimensions();

			TransformComponent& transformComponent = getComponent<TransformComponent>();
			transformComponent.translation = pos;
			transformComponent.rotation = rot;
			// Important that all meshes are in range of 1 in size because the scale depends on the dimensions from body
			transformComponent.scale = dimensions;

			// Debugger::printVec3(dimensions, "Dimensions");
			// Debugger::printVec3(transformComponent.scale, "Scale");

			glm::mat4 model = transformComponent.getTransform();
			Material& material = getComponent<Material>();
			material.bind();
			material.set("u_ViewProj", viewProj);
			material.set("u_Model", model);
			material.set("u_Color", material.getMaterialColor());
		}
	}


}