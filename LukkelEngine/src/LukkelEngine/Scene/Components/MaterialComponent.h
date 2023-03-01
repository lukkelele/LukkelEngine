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

		// s_ptr<Shader> shader = nullptr;
		s_ptr<Texture> texture = nullptr;
		MaterialType materialType = MaterialType::NORMAL;
		
		float mass = 1.0f;

		MaterialComponent() = default;
		MaterialComponent(const std::string& texturePath = "")
		{
			if (texturePath != "")
				texture = create_s_ptr<Texture>(texturePath);
			if (texturePath == "")
				LKLOG_ERROR("[MaterialComponent] String couldn't be parsed for the texture path");
		}



	};

}
