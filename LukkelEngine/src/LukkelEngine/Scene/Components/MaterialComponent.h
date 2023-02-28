#pragma once
#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/VertexBuffer.h"
#include "LukkelEngine/Renderer/IndexBuffer.h"
#include "LukkelEngine/Renderer/Shader.h"
#include "LukkelEngine/Renderer/Texture.h"

#include "glm/glm.hpp"

namespace LukkelEngine {

	struct MaterialComponent 
	{
		enum class MaterialType
		{
			NORMAL,
			ROUGH,
			SLIPPERY		
		};

		s_ptr<Shader> shader = nullptr;
		s_ptr<Texture> texture = nullptr;
		MaterialType materialType = MaterialType::NORMAL;
		
		float mass = 1.0f;

		MaterialComponent() = default;
		MaterialComponent(const std::string& shaderPath = "", const std::string& texturePath = "")
		{
			if (shaderPath != "")
				shader = create_s_ptr<Shader>(shaderPath);
			if (texturePath != "")
				texture = create_s_ptr<Texture>(texturePath);
			if (shaderPath == "" && texturePath == "")
				LKLOG_ERROR("[MaterialComponent] No strings could be parsed for both the shader path and the texture path");
			LKLOG_TRACE("MaterialComponent created");
		}



	};

}
