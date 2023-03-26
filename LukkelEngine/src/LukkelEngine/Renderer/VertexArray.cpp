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
	void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{ 
		Bind();
		vb.Bind();
		const auto& elements = layout.GetElements();
		unsigned int offset = 0;
		for (unsigned int i = 0 ; i < elements.size(); i++) {
			const auto& element = elements[i];
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, 
											layout.GetStride(), (const void*) offset));
			offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
		}
	}

	/* Bind vertex array */
	void VertexArray::Bind() const
	{
		GLCall(glBindVertexArray(m_RendererID));
	}

	/* Unbind vertex array */
	void VertexArray::Unbind() const
	{
		GLCall(glBindVertexArray(0));
	}

}
