#include "LKpch.h"
#include "Material.h"
#include "Materials.h"


namespace LukkelEngine {


	Material::Material(const std::string& shaderPath, const std::string& texturePath)
	{
		m_Shader = create_s_ptr<Shader>(shaderPath);
		m_Texture = create_s_ptr<Texture>(texturePath);
	}

	void Material::bind()
	{
		m_Shader->bind();
		m_Texture->bind();
	}

	Material& Material::create()
	{
		return Materials::DebugMaterial(); // For now
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