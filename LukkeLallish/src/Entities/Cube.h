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
			// m_Shader = create_s_ptr<Shader>("assets/shaders/basic2.shader");
			// m_Shader = create_s_ptr<Shader>("assets/shaders/3D/color3D.shader");
			m_Shader = create_s_ptr<Shader>("assets/shaders/3D/flat.shader");
			VertexBufferLayout layout;
			layout.push<float>(3); // 3D Vertex (x, y, z) 
			m_VAO->addBuffer(*m_VBO, layout);

			m_Shader->bind();
			m_Shader->setUniform4f("u_Color", 0.6f, 0.8f, 0.2f, 1.0f);
			m_TranslationA = glm::vec3(0.0f, 1.0f, 1.0f);
		}
		~Cube() = default;



	private:
		float vertices[3 * 8] = {
		-50, -50,  50, //0
		 50, -50,  50, //1
		-50,  50,  50, //2
		 50,  50,  50, //3
		-50, -50, -50, //4
		 50, -50, -50, //5
		-50,  50, -50, //6
		 50,  50, -50  //7
		};

		unsigned int indices[6 * 10] = {
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
