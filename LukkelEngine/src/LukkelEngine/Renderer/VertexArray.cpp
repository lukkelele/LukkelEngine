#include "LKpch.h"
#include "LukkelEngine/Renderer/Renderer.h"
#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/VertexBufferLayout.h"

namespace LukkelEngine {

	/* Generate vertex array and reference to it using own render ID */
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
			const auto& element = elements[i];
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, 
											layout.getStride(), (const void*) offset));
			offset += element.count * VertexBufferElement::getSizeOfType(element.type);
		}
	}

	/* Bind vertex array */
	void VertexArray::bind() const
	{
		GLCall(glBindVertexArray(m_RendererID))
	}

	/* Unbind vertex array */
	void VertexArray::unbind() const
	{
		GLCall(glBindVertexArray(0));
	}

}
