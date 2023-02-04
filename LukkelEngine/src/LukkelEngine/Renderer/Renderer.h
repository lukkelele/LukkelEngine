#pragma once

#include <GL/glew.h>
#include <VertexArray.h>
#include <Renderer/IndexBuffer.h>
#include <Renderer/Shader.h>
#include <Core/LKErrorHandler.h>

namespace LukkelEngine {

	class Renderer
	{
	public:
		void clear() const;
		void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	};
}
