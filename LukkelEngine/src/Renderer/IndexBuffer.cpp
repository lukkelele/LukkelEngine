#include <Renderer.h>
#include <IndexBuffer.h>

namespace LukkelEngine {

	IndexBuffer::IndexBuffer() { }

	IndexBuffer::IndexBuffer(const void* data, unsigned int count)
		: m_Count(count)
	{
		ASSERT(sizeof(unsigned int) == sizeof(GLuint));

		GLCall(glGenBuffers(1, &m_RendererID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER,  count * sizeof(unsigned int), data, GL_STATIC_DRAW));
	}
	 
	IndexBuffer::~IndexBuffer() 
	{
		GLCall(glDeleteBuffers(1, &m_RendererID));
	}

	void IndexBuffer::bind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	}

	void IndexBuffer::unbind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

}
