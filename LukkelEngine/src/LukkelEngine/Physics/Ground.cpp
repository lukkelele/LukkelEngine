#pragma once
#include "LKpch.h"
#include "LukkelEngine/Physics/Ground.h"


namespace LukkelEngine {

	Ground::Ground()
	{
		// FIXME: New expressions as constructor argument to hinder possible pointer problems for multiple objects ?
		m_VAO = create_s_ptr<VertexArray>();
		m_VBO = create_s_ptr<VertexBuffer>(vertices, (sizeof(vertices) / (sizeof(float)) * sizeof(float)));
		m_IBO = create_s_ptr<IndexBuffer>(indices, (sizeof(indices) / (sizeof(unsigned int)) * sizeof(unsigned int)));
		m_Shader = create_s_ptr<Shader>("assets/shaders/3D/basic.shader");
		m_Texture = std::make_unique<Texture>("assets/img/atte_square.png");

		VertexBufferLayout layout;
		layout.push<float>(3); // 3D Vertex (x, y, z) 
		layout.push<float>(2); // Texture coordinates
		// layout.push<float>(3); // RGB Color
		m_VAO->addBuffer(*m_VBO, layout);

		m_Shader->bind();
		m_Shader->setUniform4f("u_Color", 1.0f, 1.0f, 0.9f, 1.0f);
		m_Body = create_s_ptr<CollisionBody::Box>();
	}

}
