#include "LKpch.h"
#include "Material.h"
#include "Materials.h"


namespace LukkelEngine {

	// FIXME
	Material::Material()
	{ // Set default values
		std::string path = "assets/shaders/basic.shader";
		m_Shader = create_s_ptr<Shader>(path);
		LKLOG_TRACE("[MATERIAL] Creating shader using -> {0}", path);
		// m_Texture = create_s_ptr<Texture>("");
	}

	Material::Material(const std::string& shaderPath, const std::string& texturePath)
	{
		m_Shader = create_s_ptr<Shader>(shaderPath);
		m_Texture = create_s_ptr<Texture>(texturePath);
	}

	void Material::bind()
	{
		if (m_Shader) m_Shader->bind();
		if (m_Texture) m_Texture->bind();
	}

	void Material::unbind()
	{
		if (m_Shader) m_Shader->unbind();
		if (m_Texture) m_Texture->unbind();
	}

	// Material& Material::create()
	// {
	// 	// return Materials::DebugMaterial(); // For now
	// }

	template<typename T>
	void Material::set(const std::string& uniform, T& value)
	{
	}
		template<>
		void Material::set(const std::string& uniform, glm::vec4& value)
		{
			m_Shader->setUniform4f(uniform, value.x, value.y, value.z, value.w);
		}

		template<>
		void Material::set(const std::string& uniform, glm::mat4& value)
		{
			m_Shader->setUniformMat4f(uniform, value);
		}

}