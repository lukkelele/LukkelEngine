#pragma once
#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/VertexBuffer.h"
#include "LukkelEngine/Renderer/IndexBuffer.h"
#include "LukkelEngine/Renderer/Shader.h"
#include "LukkelEngine/Renderer/Texture.h"

#include "glm/glm.hpp"

namespace LukkelEngine {

	struct MeshComponent
	{
		s_ptr<VertexArray> va = nullptr;
		s_ptr<IndexBuffer> ib = nullptr;
		s_ptr<VertexBuffer> vb = nullptr;
		glm::vec3 scale{ 1.0f, 1.0f, 1.0f };
		glm::vec3 pos{ 0.0f, 0.0f, 0.0f };

		// s_ptr<Shader> shader = nullptr; // REMOVE ME

		MeshComponent() = default;

		MeshComponent(float vertices[], unsigned int indices[], const std::string& shaderPath,
							std::vector<int> vertbufLayout, unsigned int vertCount, unsigned int idxsCount)
		{
			va = create_s_ptr<VertexArray>();
			vb = create_s_ptr<VertexBuffer>(vertices, vertCount * sizeof(float));
			ib = create_s_ptr<IndexBuffer>(indices, idxsCount * sizeof(unsigned int));
			// shader = create_s_ptr<Shader>(shaderPath); // REMOVE ME
			VertexBufferLayout layout;

			for (int num : vertbufLayout) // VertexBufferLayout
				layout.push<float>(num);

			va->addBuffer(*vb, layout);
		}

	};

}
