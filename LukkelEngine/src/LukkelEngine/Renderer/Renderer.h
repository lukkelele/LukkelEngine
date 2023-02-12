#pragma once

#include "imgui/imgui.h"
#include "GL/glew.h"
#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/IndexBuffer.h"
#include "LukkelEngine/Renderer/Shader.h"
#include "LukkelEngine/Core/LKErrorHandler.h"
#include "LukkelEngine/Renderer/Camera.h"


namespace LukkelEngine {

	class Renderer
	{
	public:
		void clear() const;
		void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
		void drawImGui() const;


		// void drawIndexed(VertexArray& va, uint32_t indexCount) const;
		void drawIndexed(const s_ptr<VertexArray>& va, uint32_t indexCount) const;

		void attachCamera(Camera* cam);

		static void onWindowResize(uint16_t width, uint16_t height);
	};
}
