#include "LKpch.h"
#include "LukkelEngine/Renderer/Mesh.h"
#include "LukkelEngine/Core/Application.h"
#include "LukkelEngine/Utils/Converters.h"

namespace LukkelEngine {

	Mesh::Mesh(float vertices[], unsigned int indices[], std::vector<int> vertbufLayout, unsigned int vertCount, unsigned int indexCount)
	{
		m_VAO = create_s_ptr<VertexArray>();
		LKLOG_INFO("");
		// m_VBO = create_s_ptr<VertexBuffer>(vertices, (sizeof(vertices) / sizeof(float)) * sizeof(float));
		// m_IBO = create_s_ptr<IndexBuffer>(indices, (sizeof(indices) / sizeof(unsigned int)) * sizeof(unsigned int));
		m_VBO = create_s_ptr<VertexBuffer>(vertices, vertCount * sizeof(float));
		m_IBO = create_s_ptr<IndexBuffer>(indices, indexCount * sizeof(unsigned int));

		VertexBufferLayout layout;
		for (int num : vertbufLayout)
			layout.push<float>(num);
		m_VAO->addBuffer(*m_VBO, layout);
	}

	void Mesh::bind()
	{
		m_VAO->bind();
		m_IBO->bind();
	}

}