#pragma once

#include <vector>
#include <GLErrorHandler.h>

class VertexBufferLayout_LINUX// : VertexBufferLayout
{
private:
  std::vector<VertexBufferElement> m_Elements;
  unsigned int m_Stride;
public:
	VertexBufferLayout_LINUX() { m_Stride = 0 }
		//: m_Stride(0) {}

  inline const std::vector<VertexBufferElement> getElements() const& { return m_Elements; }
  inline unsigned int getStride() const { return m_Stride;  }
};

template<typename T>
inline void push(unsigned int count)
{
  // static_assert(false); // FIXME
}

template<>
void VertexBufferLayout::push<float>(unsigned int count)
{
  m_Elements.push_back({GL_FLOAT , count, GL_FALSE});
  m_Stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
}

template<>
void VertexBufferLayout::push<unsigned int>(unsigned int count)
{
  m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
  m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
}

template<>
void VertexBufferLayout::push<unsigned char>(unsigned int count)
{
  m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
  m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
}

