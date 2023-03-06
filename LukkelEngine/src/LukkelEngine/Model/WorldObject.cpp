#include "LKpch.h"
#include "LukkelEngine/Model/WorldObject.h"


namespace LukkelEngine {

	WorldObject::WorldObject(Mesh mesh, RigidBody rigidBody)
	{
		m_Mesh = create_u_ptr<Mesh>(mesh);
		m_RigidBody = create_u_ptr<RigidBody>(rigidBody);
	}

	WorldObject::~WorldObject()
	{
	}

	void WorldObject::onUpdate(float ts, glm::mat4 viewProj)
	{
		glm::mat4 model = m_RigidBody->getTransform();
		m_Mesh->bind();
		m_Mesh->setUniformMat4f("u_ViewProj", viewProj);
		m_Mesh->setUniformMat4f("u_Model", model);
	}

	void WorldObject::remove()
	{
	}

	glm::mat4 WorldObject::getTransform(glm::mat4& viewProj)
	{
		btTransform transform = m_RigidBody->getWorldTransform();
		btVector3 position = transform.getOrigin();
		btQuaternion rotation = transform.getRotation();

		m_Translation = glm::vec3(position.x(), position.y(), position.z());
		m_Rotation =  glm::mat4_cast(glm::quat(rotation.getW(), rotation.getX(), rotation.getY(), rotation.getZ()));

		return glm::translate(glm::mat4(1.0f), m_Translation)
				* glm::toMat4(m_Rotation)
				* glm::scale(glm::mat4(1.0f), m_Scale);
	}

	void WorldObject::addComponent(Entity& entity)
	{
	}

}