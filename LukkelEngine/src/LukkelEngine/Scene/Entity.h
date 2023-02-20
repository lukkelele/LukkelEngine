#pragma once
#include "LukkelEngine/Core/UUID.h"
#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/Shader.h"
#include "LukkelEngine/Renderer/Texture.h"

#include "entt/entt.hpp"

namespace LukkelEngine {

	class Entity
	{
	public:
		Entity();
		virtual ~Entity();
		UUID getUUID() const { return m_UUID; }

		void setVertexArray(VertexArray& va) { m_VAO = std::make_shared<VertexArray>(va); }
		void setVertexBuffer(VertexBuffer& vb) { m_VBO = std::make_shared<VertexBuffer>(vb); }
		void setIndexBuffer(IndexBuffer& ib) { m_IBO = std::make_shared<IndexBuffer>(ib); }
		void setVertexShader(Shader& shader) { m_Shader = std::make_shared<Shader>(shader); }

		s_ptr<VertexArray> getVertexArray() const { return m_VAO; }
		s_ptr<VertexBuffer> getVertexBuffer() const { return m_VBO; }
		s_ptr<IndexBuffer> getIndexBuffer() const { return m_IBO; }
		s_ptr<Shader> getShader() const { return m_Shader; }

		void setTranslation(glm::vec3& translation) { m_Translation = translation; }
		void setPosition(glm::vec3& position) { m_Position = position; }

	// TODO: Set these back to private
	public:
		// Set to unique?
		s_ptr<VertexArray> m_VAO;
		s_ptr<VertexBuffer> m_VBO;
		s_ptr<IndexBuffer> m_IBO;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Translation = { 0.0f, 0.0f, 0.0f };

		s_ptr<Shader> m_Shader;
		s_ptr<Texture> m_Texture;

	private:
		UUID m_UUID;
	};

}