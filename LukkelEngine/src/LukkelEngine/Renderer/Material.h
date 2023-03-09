#pragma once
#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Renderer/Shader.h"
#include "LukkelEngine/Renderer/Texture.h"


namespace LukkelEngine {

	class Material
	{
	public:
		Material();
		Material(const std::string& shaderPath, const std::string& texturePath);
		virtual ~Material() = default;

		void bind();
		s_ptr<Shader> getShader() const { return m_Shader; }

		glm::vec4 getMaterialColor() const { return m_Color; }
		void setMaterialColor(glm::vec4 color) { m_Color = color; }
		
		template<typename T>
		void set(const std::string& uniform, T& value);

	protected:
		s_ptr<Shader> m_Shader = nullptr;
		s_ptr<Texture> m_Texture = nullptr;
		glm::vec4 m_Color{ 1.0f, 1.0f, 1.0f, 1.0f };
	};

}