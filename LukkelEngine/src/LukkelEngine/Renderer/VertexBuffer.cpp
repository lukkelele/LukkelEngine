#include "LKpch.h"
#include "LukkelEngine/Renderer/VertexBuffer.h"
#include "LukkelEngine/Core/LKErrorHandler.h"

namespace LukkelEngine {

	VertexBuffer::VertexBuffer(const void* data, unsigned int size)
	{
		GLCall(glGenBuffers(1, &m_Count));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Count));
		GLCall(glBufferData(GL_ARRAY_BUFFER,  size, data, GL_STATIC_DRAW));
	}
	 
	VertexBuffer::~VertexBuffer() 
	{
		GLCall(glDeleteBuffers(1, &m_Count));
	}

	void VertexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Count));

	}

	void VertexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

	}

}
