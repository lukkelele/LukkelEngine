#pragma once

#include "LukkelEngine/Core/Base.h"
#include <LukkelEngine/Core/LKErrorHandler.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include "LukkelEngine/Renderer/IndexBuffer.h"

namespace LukkelEngine {

	class VertexArray
	{
	private:
		unsigned int m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
		// std::vector<s_ptr<VertexBuffer>> m_VertexBuffers;
		std::vector<VertexBuffer*> m_VertexBuffers;
		// s_ptr<IndexBuffer> m_IndexBuffer;
		IndexBuffer* m_IndexBuffer;

	public:
		VertexArray();
		~VertexArray();

		void bind() const;
		void unbind() const;
		void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
		// std::vector<s_ptr<VertexBuffer>>& getVertexBuffers() { return m_VertexBuffers;  }
		std::vector<VertexBuffer*> getVertexBuffers() { return m_VertexBuffers;  }
		// std::shared_ptr<IndexBuffer>& getIndexBuffer() { return m_IndexBuffer; }
		IndexBuffer* getIndexBuffer() { return m_IndexBuffer; }
	};

}
