#ifndef _VERTEX_BUFFER_H
#define _VERTEX_BUFFER_H


class VertexBuffer
{
private:
	unsigned int m_Count;
	
public:
	VertexBuffer();
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void bind() const;
	void unbind() const;
};

#endif // _VERTEX_BUFFER_H