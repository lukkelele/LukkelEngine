#include "LKpch.h"
#include "LukkelEngine/Model/Mesh.h"
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