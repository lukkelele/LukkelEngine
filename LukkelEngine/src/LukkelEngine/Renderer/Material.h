#pragma once
#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Renderer/Shader.h"
#include "LukkelEngine/Renderer/Texture.h"


namespace LukkelEngine {

	namespace Color {
		static const glm::vec4 White = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		static const glm::vec4 Black = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		static const glm::vec4 Gray = glm::vec4(0.33f, 0.33f, 0.33f, 1.0f);
		static const glm::vec4 Blue = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		static const glm::vec4 Red = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		static const glm::vec4 Magenta = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
		static const glm::vec4 Yellow = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
		static const glm::vec4 Silver = glm::vec4(0.75f, 0.75f, 0.75f, 1.0f);
		static const glm::vec4 Green = glm::vec4(0.0f, 0.5f, 0.0f, 1.0f);
		static const glm::vec4 Cyan = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
		static const glm::vec4 DarkGray = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
	}

	class Material
	{
	public:
		Material();
		Material(const std::string& shaderPath, const std::string& texturePath);
		Material(const std::string& vertexPath, const std::string& fragmentPath, const std::string& texturePath);
		virtual ~Material() = default;

		void Bind();
		void Unbind();
		s_ptr<Shader> GetShader() const { return m_Shader; }

		glm::vec4 GetMaterialColor() const { return m_Color; }
		glm::vec4 GetCachedMaterialColor() const { return m_CacheColor; }
		void SetMaterialColor(glm::vec4 color);
		void SetLastMaterialColor();
		
		template<typename T>
		void Set(const std::string& uniform, T& value);

	protected:
		s_ptr<Shader> m_Shader = nullptr;
		s_ptr<Texture> m_Texture = nullptr;
		glm::vec4 m_Color = Color::White;
		glm::vec4 m_CacheColor = Color::White;
	};

}