#include "LukkelEngine/Renderer/Texture.h"

#include "stb_image/stb_image.h"

namespace LukkelEngine {

	Texture::Texture(const std::string& path)
		: m_RendererID(0), m_filePath(path), m_localBuffer(nullptr), m_width(0), m_height(0), m_bpp(0)
	{
		stbi_set_flip_vertically_on_load(1);
		m_localBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);

		GLCall(glGenTextures(1, &m_RendererID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)); // S: x
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)); // T: y

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		if (m_localBuffer)
			/* might store a copy */
			stbi_image_free(m_localBuffer);
	}

	Texture::~Texture()
	{
		GLCall(glDeleteTextures(1, &m_RendererID));
	}

	void Texture::bind(unsigned int slot /*= 0*/) const
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	}

	void Texture::unbind() const
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
}
