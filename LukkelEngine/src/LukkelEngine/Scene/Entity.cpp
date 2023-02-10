#include "Entity.h"

namespace LukkelEngine {

	Entity::Entity()
	{
	}

	Entity::~Entity()
	{
	}

	void Entity::setVertexArray(VertexArray& va)
	{
		//LKLOG_TRACE("SETTINGS VAO");
		m_VAO = std::make_shared<VertexArray>(va); 
	}

	void Entity::setVertexBuffer(VertexBuffer& vb)
	{
		//LKLOG_WARN("SETTING VB");
		m_VBO = std::make_shared<VertexBuffer>(vb);
	}

	void Entity::setIndexBuffer(IndexBuffer& ib)
	{
		//LKLOG_WARN("SETTING IndexBuffer!");
		m_IBO = std::make_shared<IndexBuffer>(ib);
	}

	void Entity::setVertexShader(Shader& shader)
	{
		//LKLOG_WARN("Setting Vertex shader for entity!");
		m_VertexShader = std::make_shared<Shader>(shader);
	}

	void Entity::setFragmentShader(Shader& shader)
	{
		//LKLOG_WARN("Setting fragment shader for entity!");
		m_FragmentShader = std::make_shared<Shader>(shader);
	}

	s_ptr<VertexArray> Entity::getVertexArray()
	{
		//LKLOG_WARN("Returning shared_ptr -> VertexArray");
		return m_VAO;
	}

}