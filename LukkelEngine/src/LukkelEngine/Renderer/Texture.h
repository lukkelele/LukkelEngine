#pragma once

#include "LukkelEngine/Renderer/Renderer.h"

namespace LukkelEngine {

	class Texture
	{
	private:
		unsigned int m_RendererID;
		std::string m_filePath;
		unsigned char* m_localBuffer;
		int m_width, m_height, m_bpp; // bits per pixel

	public:
		Texture(const std::string& path);
		~Texture();

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

		inline int GetWidth() const { return m_width; }
		inline int GetHeight() const { return m_height; }
	};

}
