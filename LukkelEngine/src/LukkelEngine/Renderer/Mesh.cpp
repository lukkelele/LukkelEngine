#include "LKpch.h"
#include "LukkelEngine/Renderer/Mesh.h"
#include "LukkelEngine/Debug/Debugger.h"


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

		// glm::vec3 dimensions(0.5f, 0.5f, 0.5f);
		// glm::vec3 offset(0.0f, 0.0f, 0.0f);
		// float mass = 3.0f;
		// // NEEDED FOR RUNTIME
		// createRigidBody(dimensions, offset, mass);
	}

	void Mesh::onUpdate(float ts, glm::mat4 viewProj)
	{
		bind();
		glm::mat4 modelTransform = getTransform();
		m_Shader->setUniformMat4f("u_Model", modelTransform);
		m_Shader->setUniformMat4f("u_ViewProj", viewProj);
	}

	void Mesh::createRigidBody(glm::vec3& dimensions, glm::vec3& offset, float mass)
	{
		btVector3 dims{ dimensions.x, dimensions.y, dimensions.z };
		btVector3 off{ offset.x, offset.y, offset.z };
		m_RigidBody = create_s_ptr<RigidBodyComponent>(dims, off, mass);
		m_RigidBody->getRigidBody()->setSleepingThresholds(0.0f, 0.0f);
	}


	void Mesh::bind()
	{
		m_Shader->bind();
		m_VAO->bind();
		m_IBO->bind();
	}

	glm::mat4 Mesh::getTransform()
	{
		auto transform = m_RigidBody->getModelTransform();
		return transform;
	}


}