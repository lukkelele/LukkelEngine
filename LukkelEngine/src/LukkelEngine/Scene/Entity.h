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
		~Entity();
		UUID getUUID() const { return m_UUID; }

		void setVertexArray(VertexArray& VAO);
		void setVertexBuffer(VertexBuffer& VBO);
		void setIndexBuffer(IndexBuffer& IBO);

		void setVertexShader(Shader& shader);
		void setFragmentShader(Shader& shader);

		s_ptr<VertexArray>& getVertexArray();// { return m_VAO; }
		s_ptr<VertexBuffer>& getVertexBuffer();
		s_ptr<IndexBuffer>& getIndexBuffer();
		s_ptr<Shader>& getVertexShader() { return m_VertexShader; }
		s_ptr<Shader>& getFragmentShader() { return m_FragmentShader; }

	private:
		UUID m_UUID;
		// Set to unique?
		s_ptr<VertexArray> m_VAO;
		s_ptr<VertexBuffer> m_VBO;
		s_ptr<IndexBuffer> m_IBO;

		s_ptr<Shader> m_VertexShader;
		s_ptr<Shader> m_FragmentShader;

		// ----
		// Scene* m_Scene; // BUGGED!!!!
	};

}