#include "Entity.h"

namespace LukkelEngine {

	Entity::Entity()
	{
	}

	Entity::~Entity()
	{
	}

	/**
	 * @brief Get translation for a body in world space
	 * @return a glm::vec3 vector (x, y, z) for the body in space
	*/
	glm::vec3 Entity::getWorldTransform()
	{
		btTransform transform;
		m_RigidBody->getMotionState()->getWorldTransform(transform);
		btVector3 tv = transform.getOrigin();

		return glm::vec3(tv.getX(), tv.getY(), tv.getZ());
	}

	/**
	 * @brief Get the translation matrix for the entity
	 * @return glm::mat4 translation matrix
	*/
	glm::mat4 Entity::getEntityTranslation()
	{
		glm::mat4 model(1.0f);
		glm::vec3 translation = getWorldTransform();
		glm::mat4 modelTranslation = glm::translate(model, translation);
		return modelTranslation;
	}

	/**
	 * @brief Update entity position in the world (3D space)
	 * Binds texture and shader applies view projection multiplication
	 * @param projectionMatrix is the projection matrix from the 3D camera
	*/
	void Entity::updateOrientation(glm::mat4 projectionMatrix)
	{
		m_Shader->bind();
		m_Texture->bind();
		glm::mat4 modelTransform = getEntityTranslation();
		m_Shader->setUniformMat4f("u_Model", modelTransform);
		m_Shader->setUniformMat4f("u_ViewProj", projectionMatrix);
	}
}