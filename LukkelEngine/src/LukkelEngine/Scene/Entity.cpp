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
		if (hasComponent<Rigidbody>())
		{
			// if the entity has a rigidbody, sync the body with the transform component
			Rigidbody& rigidbody = getComponent<Rigidbody>();
			TransformComponent& transformComponent = getComponent<TransformComponent>();

			auto [pos, rot] = rigidbody.getPosAndRotation();
			glm::vec3 dimensions = rigidbody.getDimensions();

			auto lv = rigidbody.getLinearVelocity();

			transformComponent.translation = pos;
			transformComponent.rotation = rot;
			transformComponent.scale = dimensions;

			glm::mat4 model = transformComponent.getTransform();
			Material& material = getComponent<Material>();
			material.bind();
			material.set("u_ViewProj", viewProj);
			material.set("u_Model", model);
			material.set("u_Color", material.getMaterialColor());
		}
	}


}