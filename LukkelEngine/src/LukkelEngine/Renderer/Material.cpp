#include "LKpch.h"
#include "Material.h"
#include "Materials.h"


namespace LukkelEngine {

	Material::Material()
	{
		std::string vertexPath = "assets/shaders/basic.vertex";
		std::string fragmentPath = "assets/shaders/basic.fragment";
		m_Shader = create_s_ptr<Shader>(vertexPath, fragmentPath);
		m_Texture = create_s_ptr<Texture>("");
	}

	Material::Material(const std::string& shaderPath, const std::string& texturePath)
	{
		m_Shader = create_s_ptr<Shader>(shaderPath);
		m_Texture = create_s_ptr<Texture>(texturePath);
	}

	Material::Material(const std::string& vertexPath, const std::string& fragmentPath, const std::string& texturePath)
	{
		m_Shader = create_s_ptr<Shader>(vertexPath, fragmentPath);
		m_Texture = create_s_ptr<Texture>(texturePath);
	}

	void Material::SetMaterialColor(glm::vec4 color)
	{
		if (color != m_Color)
		{
			m_CacheColor = m_Color;
			m_Color = color;
		}
	}

	void Material::SetLastMaterialColor()
	{
		m_Color = m_CacheColor;
	}

	void Material::Bind()
	{
		if (m_Shader) m_Shader->Bind();
		if (m_Texture) m_Texture->Bind();
	}

	void Material::Unbind()
	{
		if (m_Shader) m_Shader->Unbind();
		if (m_Texture) m_Texture->Unbind();
	}

	template<typename T>
	void Material::Set(const std::string& uniform, T& value)
	{
	}
		template<>
		void Material::Set(const std::string& uniform, glm::vec4& value)
		{
			m_Shader->SetUniform4f(uniform, value.x, value.y, value.z, value.w);
		}

		template<>
		void Material::Set(const std::string& uniform, glm::mat4& value)
		{
			m_Shader->SetUniformMat4f(uniform, value);
		}

}