#pragma once

namespace LukkelEngine {

	class IndexBuffer
	{
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
		
	public:
		IndexBuffer();
		IndexBuffer(const void* data, unsigned int count);
		~IndexBuffer();

		void bind() const;
		void unbind() const;

		inline unsigned int getCount() const { return m_Count;  }
	};
}
