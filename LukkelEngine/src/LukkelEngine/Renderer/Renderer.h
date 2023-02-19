#pragma once

#include "imgui/imgui.h"
#include "GL/glew.h"

#include "LukkelEngine/Core/LKErrorHandler.h"
#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/IndexBuffer.h"
#include "LukkelEngine/Renderer/Shader.h"
#include "LukkelEngine/Renderer/Camera.h"
// #include "LukkelEngine/Scene/Entity.h"


namespace LukkelEngine {

	class Renderer
	{
	public:
		void clear() const;
		void draw(const VertexArray& va,
				  const IndexBuffer& ib,
				  const Shader& shader) const;
		void drawLines(const VertexArray& va,
					   const IndexBuffer& ib,
					   const Shader& shader) const;

		//void draw(Entity& entity);
		//void drawLines(Entity& entity);
		void drawImGui() const;

		static void onWindowResize(uint16_t width, uint16_t height);
	};
}
