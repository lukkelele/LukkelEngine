#pragma once

#include "LukkelEngine/Scene/Entity.h"

namespace LukkelEngine {

	class Rectangle : public Entity
	{
	public:
		Rectangle()
		{
			m_VAO = create_s_ptr<VertexArray>();
			m_VBO = create_s_ptr<VertexBuffer>(vertices, (sizeof(vertices) / (sizeof(float)) * sizeof(float)));
			m_IBO = create_s_ptr<IndexBuffer>(indices, (sizeof(indices) / (sizeof(unsigned int)) * sizeof(unsigned int)));
			// m_Shader = create_s_ptr<Shader>("../res/shaders/basic2.shader");
			m_Shader = create_s_ptr<Shader>("assets/shaders/basic2.shader");
			VertexBufferLayout layout;
			layout.push<float>(2); // 2D Vertex (x, y) 
			m_VAO->addBuffer(*m_VBO, layout);
			m_Shader->bind();
			m_Shader->setUniform4f("u_Color", 0.6f, 0.8f, 0.2f, 1.0f);
		}

		~Rectangle() = default;

	private:
		float vertices[8] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f
		};

		unsigned int indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		float vertices_tex[16] = {
			-50.0f, -50.0f, 0.0f, 0.0f,
			 50.0f, -50.0f, 1.0f, 0.0f,
			 50.0f,  50.0f, 1.0f, 1.0f,
			-50.0f,  50.0f, 0.0f, 1.0f
		};

		unsigned int indices_tex[6] = {
			0, 1, 2,
			2, 3, 0
		};

	};
}

