#pragma once

#include <vector>
#include <GLErrorHandler.h>
#include <VertexBufferLayout.h>


class VertexBufferLayout_WINDOWS // : VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;

public:
	VertexBufferLayout_WINDOWS() { m_Stride = 0 }

	template<typename T>
	void push(unsigned int count)
	{
		// static_assert(false); // FIXME
	}

	template<>
	void push<float>(unsigned int count)
	{
		m_Elements.push_back({GL_FLOAT , count, GL_FALSE});
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
	}

	template<>
	void push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
		m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement> getElements() const& { return m_Elements; }
	inline unsigned int getStride() const { return m_Stride;  }
};
