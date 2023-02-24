#include "LKpch.h"
#include "Entity.h"

namespace LukkelEngine {

	Entity::Entity()
	{
	}

	Entity::~Entity()
	{
	}

	/**
	 * @brief Get the model matrix for the entity
	 * @return glm::mat4 model matrix
	*/
	glm::mat4 Entity::getModelMatrix(float scale)
	{
		glm::mat4 model(1.0f);
		btTransform transform;
		m_Body->getRigidBody()->getMotionState()->getWorldTransform(transform);
		btVector3 translate = transform.getOrigin();
		btQuaternion rotation = transform.getRotation();
		glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), rotation.getAngle(),
			glm::vec3(rotation.getAxis().getX(), rotation.getAxis().getY(), rotation.getAxis().getZ()));

		glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
		glm::mat4 transMat = glm::translate(glm::mat4(1.0f), glm::vec3(translate.getX(), translate.getY(), translate.getZ()));
		glm::mat4 modelMatrix = transMat * rotMat * scaleMat;
		return modelMatrix;
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
		glm::mat4 modelTransform = getModelMatrix();
		m_Shader->setUniformMat4f("u_Model", modelTransform);
		m_Shader->setUniformMat4f("u_ViewProj", projectionMatrix);
	}
}