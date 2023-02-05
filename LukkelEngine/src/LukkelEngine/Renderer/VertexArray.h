#pragma once

#include <LukkelEngine/Core/LKErrorHandler.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>

namespace LukkelEngine {

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

}
