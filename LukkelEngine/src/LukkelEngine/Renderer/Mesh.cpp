#include "LKpch.h"
#include "LukkelEngine/Renderer/Mesh.h"
#include "LukkelEngine/Debug/Debugger.h"
#include "LukkelEngine/Core/Application.h"

namespace LukkelEngine {

	Mesh::Mesh()
	{
	}

	Mesh::Mesh(float vertices[], unsigned int indices[], const std::string& shaderPath,
					std::vector<int> vertbufLayout, unsigned int vertCount, unsigned int idxsCount)
	{
		m_VAO = create_s_ptr<VertexArray>();
		m_VBO = create_s_ptr<VertexBuffer>(vertices, vertCount * sizeof(float));
		m_IBO = create_s_ptr<IndexBuffer>(indices, idxsCount * sizeof(unsigned int));
		m_Shader = create_s_ptr<Shader>(shaderPath);

		VertexBufferLayout layout;
		for (int num : vertbufLayout)
			layout.push<float>(num);
		m_VAO->addBuffer(*m_VBO, layout);
	}

	void Mesh::bind()
	{
		m_Shader->bind();
		m_VAO->bind();
		m_IBO->bind();
	}

	void Mesh::onUpdate(float ts, glm::mat4 viewProj)
	{
		glm::mat4 model = m_RigidBody->getTransform();
		bind();
		m_Shader->setUniformMat4f("u_ViewProj", viewProj);
		m_Shader->setUniformMat4f("u_Model", model);
	}

	void Mesh::createRigidBody(glm::vec3& dimensions, glm::vec3& offset, float mass, RigidBody::Type bodyType)
	{
		btVector3 dims{ dimensions.x, dimensions.y, dimensions.z };
		btVector3 off{ offset.x, offset.y, offset.z };
		m_RigidBody = create_s_ptr<RigidBody>(dims, off, mass, bodyType);
		auto rigidbody = m_RigidBody->getRigidBody();

		switch (bodyType)
		{
			case RigidBody::Type::KINEMATIC:
				rigidbody->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
				rigidbody->setActivationState(DISABLE_DEACTIVATION);
				break;

			case RigidBody::Type::STATIC:
				rigidbody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
				rigidbody->setActivationState(DISABLE_DEACTIVATION);
				break;
		}
	}

	glm::mat4 Mesh::createModelMatrix(btTransform& transform)
	{
		btScalar matrix[16];
		transform.getOpenGLMatrix(matrix);
		glm::mat4 modelMatrix(matrix[0], matrix[1], matrix[2], matrix[3],
							  matrix[4], matrix[5], matrix[6], matrix[7],
							  matrix[8], matrix[9], matrix[10], matrix[11],
							  matrix[12], matrix[13], matrix[14], matrix[15]);
		return modelMatrix;
	}


}