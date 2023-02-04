#include <Renderer.h>
#include <VertexArray.h>
#include <VertexBufferLayout.h>

namespace LukkelEngine {

	VertexArray::VertexArray()
	{
		GLCall(glGenVertexArrays(1, &m_RendererID));
		GLCall(glBindVertexArray(m_RendererID));
	}

	VertexArray::~VertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &m_RendererID));
	}

	/* Adds buffer and configures appropriate layout */
	void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{ 
		bind();
		vb.bind();
		const auto& elements = layout.getElements();
		unsigned int offset = 0;
		for (unsigned int i = 0 ; i < elements.size(); i++) {
			std::cout << "i == " << i << std::endl;
			const auto& element = elements[i];
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, 
											layout.getStride(), (const void*) offset));
			offset += element.count * VertexBufferElement::getSizeOfType(element.type);
		}
	}

	void VertexArray::bind() const
	{
		GLCall(glBindVertexArray(m_RendererID))
	}

	void VertexArray::unbind() const
	{
		GLCall(glBindVertexArray(0));
	}

}
