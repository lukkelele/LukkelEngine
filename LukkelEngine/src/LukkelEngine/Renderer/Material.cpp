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