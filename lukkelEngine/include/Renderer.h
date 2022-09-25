#ifndef _RENDERER_H
#define _RENDERER_H

#include <GL/glew.h>
#include <GLErrorHandler.h>

#include <VertexArray.h>
#include <IndexBuffer.h>
#include <Shader.h>


class Renderer
{
public:
	void clear() const;
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};


#endif // _RENDERER_H