#pragma once

#include "imgui/imgui.h"
#include "GL/glew.h"

#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Core/LKErrorHandler.h"
#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/IndexBuffer.h"
#include "LukkelEngine/Renderer/Shader.h"


namespace LukkelEngine {

	class Renderer
	{
	public:
		void clear() const;
		void drawFill(const VertexArray& va,
				  const IndexBuffer& ib,
				  const Shader& shader) const;
		void drawLines(const VertexArray& va,
					   const IndexBuffer& ib,
					   const Shader& shader) const;
		void drawIndexed(const s_ptr<VertexArray>& va);

		void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
		void renderImGui() const;

		static void onWindowResize(uint16_t width, uint16_t height);

		// static uint8_t s_DrawMode;
		static bool s_DrawMode;
	};
}
