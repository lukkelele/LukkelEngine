#include <VertexBuffer.h>
#include <Renderer.h>

namespace LukkelEngine {

	VertexBuffer::VertexBuffer() { }

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

	void VertexBuffer::bind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Count));

	}

	void VertexBuffer::unbind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

	}


}
