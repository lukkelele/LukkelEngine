#pragma once

#include "LukkelEngine/Scene/Entity.h"

namespace LukkelEngine {

	class Cube : public Entity
	{
	public:
		Cube()
		{
			m_VAO = create_s_ptr<VertexArray>();
			m_VBO = create_s_ptr<VertexBuffer>(vertices, (sizeof(vertices) / (sizeof(float)) * sizeof(float)));
			m_IBO = create_s_ptr<IndexBuffer>(indices, (sizeof(indices) / (sizeof(unsigned int)) * sizeof(unsigned int)));
			m_Shader = create_s_ptr<Shader>("assets/shaders/3D/flat.shader");
			// m_Texture = std::make_unique<Texture>("assets/img/atte_square.png"); // FIXME: Sandbox pathing
			m_Texture = std::make_unique<Texture>("assets/img/debug_texture.png"); // FIXME: Sandbox pathing

			VertexBufferLayout layout;
			layout.push<float>(3); // 3D Vertex (x, y, z) 
			layout.push<float>(2);
			m_VAO->addBuffer(*m_VBO, layout);

			m_Shader->bind();
			m_Shader->setUniform4f("u_Color", 1.0f, 1.0f, 0.9f, 1.0f);
		}
		~Cube() = default;

	private:
		float vertices[100] = {
		// Positions		   Texture coordinates
		-0.5f, -0.5f,  0.5f,   0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f
		};
		
		float vvertices[5 * 8] = {
			1.0f,  1.0f,  0.0f,   0.0f, 1.0f, // 0 - 0 0 0
			1.0f, -1.0f,  0.0f,   1.0f, 0.0f, // 1 - 1 0 0
		   -1.0f, -1.0f,  0.0f,   1.0f, 1.0f, // 2 - 1 0 1
		   -1.0f,  1.0f,  0.0f,   1.0f, 1.0f, // 3 - 1 1 0

			1.0f,  1.0f, -1.0f,   0.0f, 1.0f, // 4 - 1 1 1
			1.0f, -1.0f, -1.0f,   0.0f, 1.0f, // 5 - 0 1 1
		   -1.0f, -1.0f, -1.0f,   1.0f, 1.0f, // 6 - 0 1 0
		   -1.0f,  1.0f, -1.0f,   0.0f, 0.0f  // 7 - 0 0 1
		};

		 unsigned int iindices[36] = {
			// front
			0, 1, 3,
			1, 2, 3,
			// back
			4, 5, 7,
			5, 6, 7,
			// right
			0, 1, 4,
			1, 4, 5,
			// left
			2, 3, 7,
			2, 6, 7,
			// top
			0, 3, 4,
			3, 4, 7,
			// bottom
			1, 2, 5,
			2, 5, 6
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
