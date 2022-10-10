#include <Renderer.h>
#include <VertexArray.h>

#include <VertexBufferLayout.h>



VertexArray::VertexArray()
{
	LCall(glGenVertexArrays(1, &m_RendererID));
	LCall(glBindVertexArray(m_RendererID));
}

VertexArray::~VertexArray()
{
	LCall(glDeleteVertexArrays(1, &m_RendererID));
}

/* Adds buffer and configures appropriate layout */
void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{ 
	bind();
	vb.bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0 ; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		LCall(glEnableVertexAttribArray(i));
		LCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, 
									    layout.getStride(), (const void*) offset));
		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	}
}

void VertexArray::bind() const
{
	LCall(glBindVertexArray(m_RendererID))
}

void VertexArray::unbind() const
{
	LCall(glBindVertexArray(0));
}

