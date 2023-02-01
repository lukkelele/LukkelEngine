#pragma once

#include <GLErrorHandler.h>

#include <VertexBuffer.h>
#if defined _WINDOWS_x64 || _WINDOWS_x86
  #include <VertexBufferLayout_WINDOWS.h>
  typedef VertexBufferLayout_WINDOWS VertexBufferLayout;
#else
  #include <VertexBufferLayout_LINUX.h>
  typedef VertexBufferLayout_LINUX VertexBufferLayout;
#endif
// #include <VertexBufferLayout.h>


class VertexArray
{
private:
	unsigned int m_RendererID;

public:
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void bind() const;
	void unbind() const;
};
