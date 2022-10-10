#include <Renderer.h>
#include <IndexBuffer.h>


IndexBuffer::IndexBuffer(const void* data, unsigned int count)
    : m_Count(count)
{
    //ASSERT(sizeof(unsigned int) == sizeof(GLuint)); // FIXME

    LCall(glGenBuffers(1, &m_RendererID));
    LCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    LCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER,  count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}
 
IndexBuffer::~IndexBuffer() 
{
    LCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::bind() const
{
    LCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::unbind() const
{
    LCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
