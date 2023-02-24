#pragma once

#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Physics/Box.h"

namespace LukkelEngine {

	class Cube : public Entity
	{
	public:
		Cube()
		{
			// FIXME: New expressions as constructor argument to hinder possible pointer problems for multiple objects ?
			m_VAO = create_s_ptr<VertexArray>();
			m_VBO = create_s_ptr<VertexBuffer>(vertices, (sizeof(vertices) / (sizeof(float)) * sizeof(float)));
			m_IBO = create_s_ptr<IndexBuffer>(indices, (sizeof(indices) / (sizeof(unsigned int)) * sizeof(unsigned int)));
			// m_Shader = create_s_ptr<Shader>("assets/shaders/3D/flat.shader");
			m_Shader = create_s_ptr<Shader>("assets/shaders/3D/basic.shader");
			// m_Texture = std::make_unique<Texture>("assets/img/debug_texture.png");
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
		~Cube() = default;

	private:
		float vertices[8 * 8] = {
		// Positions		 Texture coords    Color
		-0.5f, -0.5f,  0.5f,   0.0f, 1.0f,    // 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,   1.0f, 0.0f,    // 0.2f, 0.5f, 0.0f,
		-0.5f,  0.5f,  0.5f,   1.0f, 1.0f,    // 1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 1.0f,    // 0.3f, 0.5f, 0.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,    // 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,   0.0f, 1.0f,    // 0.0f, 0.5f, 0.5f,
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f,    // 0.7f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f,    // 1.0f, 0.5f, 0.0f
		};

		float vertices_color[8 * 8] = {
		// Positions		 Texture coords    Color
		-0.5f, -0.5f,  0.5f,   0.0f, 1.0f,    1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,   1.0f, 0.0f,    0.2f, 0.5f, 0.0f,
		-0.5f,  0.5f,  0.5f,   1.0f, 1.0f,    1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 1.0f,    0.3f, 0.5f, 0.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,    0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,   0.0f, 1.0f,    0.0f, 0.5f, 0.5f,
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f,    0.7f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f,    1.0f, 0.5f, 0.0f
		};
		
		// 6 Sides
		// Should go anticlockwise
		unsigned int indices[6 * 6] = {
			//Top
			2, 6, 7,
			2, 3, 7,
			//Bottom
			0, 4, 5,
			0, 1, 5,
			//Left
			0, 2, 6,
			0, 4, 6,
			//Right
			1, 3, 7,
			1, 5, 7,
			//Front
			0, 2, 3,
			0, 1, 3,
			//Back
			4, 6, 7,
			4, 5, 7
		};
	};
}

