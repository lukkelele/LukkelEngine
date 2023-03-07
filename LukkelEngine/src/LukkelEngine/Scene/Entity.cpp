#include "LKpch.h"
#include "LukkelEngine/Scene/Entity.h"


namespace LukkelEngine {

	Entity::Entity(Mesh mesh, RigidBody rigidBody, Material material)
	{
		m_Mesh = create_u_ptr<Mesh>(mesh);
		m_RigidBody = create_u_ptr<RigidBody>(rigidBody);
		m_Material = create_u_ptr<Material>(material);
	}

	 Entity::Entity(entt::entity handle, Scene* scene)
	 	: m_EntityHandle(handle), m_Scene(scene)
	 {
	 }

	void Entity::onUpdate(float ts, glm::mat4 viewProj)
	{
		LKLOG_WARN("Getting model transform");
		glm::mat4 model = getTransform(viewProj);
		m_Material->bind();
		LKLOG_TRACE("Setting view proj on shader");
		m_Material->set("u_ViewProj", viewProj);
		LKLOG_TRACE("Setting model on shader");
		m_Material->set("u_Model", model);
	}

	void Entity::remove()
	{
	}

	glm::mat4 Entity::getTransform(glm::mat4& viewProj)
	{
		LKLOG_WARN("Getting rigidbody world transform");
		btTransform transform = m_RigidBody->getWorldTransform();
		LKLOG_WARN("Getting rigidbody world origin and rotation");
		btVector3 position = transform.getOrigin();
		btQuaternion rotation = transform.getRotation();

		LKLOG_WARN("Creating translation and rotation matrices");
		m_Translation = glm::vec3(position.x(), position.y(), position.z());
		m_Rotation =  glm::mat4_cast(glm::quat(rotation.getW(), rotation.getX(), rotation.getY(), rotation.getZ()));

		LKLOG_TRACE("Returning translation matrix");
		return glm::translate(glm::mat4(1.0f), m_Translation)
				* glm::toMat4(m_Rotation)
				* glm::scale(glm::mat4(1.0f), m_Scale);
	}


}