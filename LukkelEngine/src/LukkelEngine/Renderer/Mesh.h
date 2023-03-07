#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/VertexBuffer.h"
#include "LukkelEngine/Renderer/IndexBuffer.h"

namespace LukkelEngine {

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 tangent;
		glm::vec3 binormal;
		glm::vec2 texcoord;
	};

	typedef glm::vec3 Index;

	class Mesh
	{
	public:
		Mesh() = default;
		Mesh(float vertices[], unsigned int indices[], std::vector<int> vertbufLayout);
		~Mesh() = default;

		void bind();
		s_ptr<IndexBuffer> getIndexBuffer() { return m_IBO; }

	private:
		s_ptr<VertexArray> m_VAO;
		s_ptr<IndexBuffer> m_IBO;
		s_ptr<VertexBuffer> m_VBO;
	};

	// Upcoming implementation
	// Mesh(std::vector<Vertex> vertices, std::vector<Index> indices, std::vector<int> vertbufLayout);
}