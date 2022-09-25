#ifndef _VERTEX_ARRAY_H
#define _VERTEX_ARRAY_H

#include <GLErrorHandler.h>

#include <VertexBuffer.h>
#include <VertexBufferLayout.h>


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

#endif /* _VERTEX_ARRAY_H */