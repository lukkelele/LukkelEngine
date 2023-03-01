#pragma once

#include "imgui/imgui.h"
#include "GL/glew.h"

#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Core/LKErrorHandler.h"
#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/IndexBuffer.h"
#include "LukkelEngine/Renderer/Shader.h"

// TODO: Move to pch (?)
// Draw modes
typedef uint8_t LK_DRAW_MODE;
#define LK_DRAW_TRIANGLES  GL_TRIANGLES
#define LK_DRAW_LINES	   GL_LINES
#define LK_DRAW		       LK_DRAW_TRIANGLES // Initial value


namespace LukkelEngine {

	class Renderer
	{
	public:
		void clear() const;

		void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
		void drawTriangles(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
		void drawLines(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
		void drawIndexed(const s_ptr<VertexArray>& va);

		void renderImGui() const;

		void setDrawMode(LK_DRAW_MODE drawMode);

		static void onWindowResize(uint16_t width, uint16_t height);

		static LK_DRAW_MODE s_DrawMode;
	};
}
