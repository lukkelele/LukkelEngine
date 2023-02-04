#pragma once

#include <GL/glew.h>
#include <VertexArray.h>
#include <IndexBuffer.h>
#include <Shader.h>
#include <LKErrorHandler.h>

namespace LukkelEngine {

	class Renderer
	{
	public:
		void clear() const;
		void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	};
}
