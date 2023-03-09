#include "LKpch.h"
#include "LukkelEngine/Scene/Entity.h"


namespace LukkelEngine {


	 Entity::Entity(entt::entity handle, Scene* scene)
	 	: m_EntityHandle(handle), m_Scene(scene)
	 {
	 }

	// Remove
	void Entity::onUpdate(float ts, glm::mat4 viewProj)
	{
		glm::mat4 model = getTransform(viewProj);
		Material& material = getComponent<Material>();
		material.bind();
		material.set("u_ViewProj", viewProj);
		material.set("u_Model", model);
	}

	void Entity::remove()
	{
	}

	glm::mat4 Entity::getTransform(glm::mat4& viewProj)
	{
		auto rigidbody = getComponent<RigidBody>();
		btTransform transform = rigidbody.getWorldTransform();
		btVector3 position = transform.getOrigin();
		btQuaternion rotation = transform.getRotation();

		m_Translation = glm::vec3(position.x(), position.y(), position.z());
		m_Rotation =  glm::mat4_cast(glm::quat(rotation.getW(), rotation.getX(), rotation.getY(), rotation.getZ()));

		return glm::translate(glm::mat4(1.0f), m_Translation)
				* glm::toMat4(m_Rotation)
				* glm::scale(glm::mat4(1.0f), m_Scale);
	}


}