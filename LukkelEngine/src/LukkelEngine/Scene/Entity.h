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

		//VertexArray& getVertexArray() { return *m_VAO; }
		//VertexBuffer& getVertexBuffer() { return *m_VBO; }
		//IndexBuffer& getIndexBuffer() { return *m_IBO; }
		//Shader& getVertexShader() { return *m_VertexShader; }
		//Shader& getFragmentShader() { return *m_FragmentShader; }

		//void setVertexArray(VertexArray& VAO) { m_VAO = VAO; }
		//void setVertexBuffer(VertexBuffer& VBO) { m_VBO = VBO; }
		//void setIndexBuffer(IndexBuffer& IBO) { m_IBO = IBO; }
		//void setVertexShader(Shader& shader) { m_VertexShader = shader; }
		//void setFragmentShader(Shader& shader) { m_FragmentShader = shader; }

		s_ptr<VertexArray> getVertexArray();// { return m_VAO; }
		s_ptr<VertexBuffer> getVertexBuffer() { return m_VBO; }
		s_ptr<IndexBuffer> getIndexBuffer() { return m_IBO; }
		s_ptr<Shader> getVertexShader() { return m_VertexShader; }
		s_ptr<Shader> getFragmentShader() { return m_FragmentShader; }

	private:
		UUID m_UUID;
		//u_ptr<VertexArray> m_VAO;
		//u_ptr<VertexBuffer> m_VBO;
		//u_ptr<IndexBuffer> m_IBO;

		//u_ptr<Shader> m_VertexShader;
		//u_ptr<Shader> m_FragmentShader;

		s_ptr<VertexArray> m_VAO;
		s_ptr<VertexBuffer> m_VBO;
		s_ptr<IndexBuffer> m_IBO;

		s_ptr<Shader> m_VertexShader;
		s_ptr<Shader> m_FragmentShader;

		//VertexArray* m_VAO;
		//VertexBuffer* m_VBO;
		//IndexBuffer* m_IBO;

		//Shader* m_VertexShader;
		//Shader* m_FragmentShader;

		// ----
		// Scene* m_Scene; // BUGGED!!!!
	};

}