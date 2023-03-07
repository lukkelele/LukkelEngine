#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/VertexBuffer.h"
#include "LukkelEngine/Renderer/IndexBuffer.h"
#include "LukkelEngine/Renderer/Shader.h"
#include "LukkelEngine/Renderer/Texture.h"


namespace LukkelEngine {

	class Mesh
	{
	public:
		Mesh();
		Mesh(float vertices[], unsigned int indices[], const std::string& shaderPath,
				std::vector<int> vertbufLayout, unsigned int vertCount, unsigned int idxsCount);
		~Mesh() = default;

		void bind();
		s_ptr<Shader> getShader() { return m_Shader; }
		s_ptr<Texture> getTexture() { return m_Texture; }
		s_ptr<IndexBuffer> getIndexBuffer() { return m_IBO; }

		void setUniform4f(const std::string uniformName, glm::vec4& vec4);
		void setUniformMat4f(const std::string uniformName, glm::mat4& mat);

		glm::mat4 createModelMatrix(btTransform& transform);

	private:
		s_ptr<VertexArray> m_VAO;
		s_ptr<IndexBuffer> m_IBO;
		s_ptr<VertexBuffer> m_VBO;
		s_ptr<Shader> m_Shader;
		s_ptr<Texture> m_Texture;
	};

}