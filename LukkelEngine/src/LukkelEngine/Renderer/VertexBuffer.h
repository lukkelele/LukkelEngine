#pragma once

namespace LukkelEngine {

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

}
