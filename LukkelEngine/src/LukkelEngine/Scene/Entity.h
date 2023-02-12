#pragma once
#include "LukkelEngine/Core/UUID.h"
#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/Shader.h"

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
		void setFragmentShader(Shader& shader) { m_FragmentShader = std::make_shared<Shader>(shader); }
		void setVertexShader(Shader& shader) { m_Shader = std::make_shared<Shader>(shader); }

		s_ptr<VertexArray> getVertexArray() const { return m_VAO; }
		s_ptr<VertexBuffer> getVertexBuffer() const { return m_VBO; }
		s_ptr<IndexBuffer> getIndexBuffer() const { return m_IBO; }
		s_ptr<Shader> getVertexShader() const { return m_Shader; }
		s_ptr<Shader> getFragmentShader() const { return m_FragmentShader; }


	// TODO: Set these back to private
	public:
		// Set to unique?
		s_ptr<VertexArray> m_VAO;
		s_ptr<VertexBuffer> m_VBO;
		s_ptr<IndexBuffer> m_IBO;

		glm::vec3 m_TranslationA; // For testing

		s_ptr<Shader> m_Shader;
		s_ptr<Shader> m_FragmentShader; // TODO: Rename this

	private:
		UUID m_UUID;
	};

}