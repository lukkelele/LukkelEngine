#pragma once
#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Core/LKErrorHandler.h"
#include "LukkelEngine/Renderer/VertexBuffer.h"
#include "LukkelEngine/Renderer/VertexBufferLayout.h"
#include "LukkelEngine/Renderer/IndexBuffer.h"


namespace LukkelEngine {

	class VertexArray
	{
	private:
		unsigned int m_RendererID; // MOVE ME TO PRIVATE
		uint32_t m_VertexBufferIndex = 0;
		std::vector<s_ptr<VertexBuffer>> m_VertexBuffers;
		s_ptr<IndexBuffer> m_IndexBuffer;

	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;
		void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
		std::vector<s_ptr<VertexBuffer>>& GetVertexBuffers() { return m_VertexBuffers;  }
		s_ptr<IndexBuffer>& GetIndexBuffer() { return m_IndexBuffer; }

	};

}
