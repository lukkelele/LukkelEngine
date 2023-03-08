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
		// static Material& create();
		// virtual void onReload();
		// virtual void copy(const Material& other, const std::string& name);
		// virtual void create(const Material&, const std::string& name);
		// virtual void detachShader();
		
		template<typename T>
		void set(const std::string& uniform, T& value);

	protected:
		s_ptr<Shader> m_Shader = nullptr;
		s_ptr<Texture> m_Texture = nullptr;
	};

}