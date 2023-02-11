#include "Entity.h"

namespace LukkelEngine {

	Entity::Entity()
	{
		s_ptr<VertexArray> m_VAO;
		s_ptr<VertexBuffer> m_VBO;
		s_ptr<IndexBuffer> m_IBO;
	}

	Entity::~Entity()
	{
	}

	void Entity::setVertexArray(VertexArray& va) { m_VAO = std::make_shared<VertexArray>(va); }

	void Entity::setVertexBuffer(VertexBuffer& vb) { m_VBO = std::make_shared<VertexBuffer>(vb); }

	void Entity::setIndexBuffer(IndexBuffer& ib) { m_IBO = std::make_shared<IndexBuffer>(ib); }

	void Entity::setVertexShader(Shader& shader) { m_VertexShader = std::make_shared<Shader>(shader); }

	void Entity::setFragmentShader(Shader& shader) { m_FragmentShader = std::make_shared<Shader>(shader); }
}