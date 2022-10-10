#include <VertexBuffer.h>
#include <Renderer.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    LCall(glGenBuffers(1, &m_Count));
    LCall(glBindBuffer(GL_ARRAY_BUFFER, m_Count));
    LCall(glBufferData(GL_ARRAY_BUFFER,  size, data, GL_STATIC_DRAW));

}
 
VertexBuffer::~VertexBuffer() 
{
    LCall(glDeleteBuffers(1, &m_Count));
}

void VertexBuffer::bind() const
{
    LCall(glBindBuffer(GL_ARRAY_BUFFER, m_Count));

}

void VertexBuffer::unbind() const
{
    LCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

}
