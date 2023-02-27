#pragma once
#include "LukkelEngine/Debug/Test/Test.h"
#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/VertexBufferLayout.h"
#include "LukkelEngine/Renderer/VertexBuffer.h"
#include "LukkelEngine/Renderer/IndexBuffer.h"
#include "LukkelEngine/Renderer/Texture.h"
#include "LukkelEngine/Renderer/Shader.h"

#include <glm/ext.hpp>

namespace LukkelEngine {

	namespace test {

		class TestDrawCube : public Test
		{
		public:
			TestDrawCube();
			~TestDrawCube();

			std::unique_ptr<VertexArray> m_VAO;
			std::unique_ptr<VertexBuffer> m_VBO;
			std::unique_ptr<IndexBuffer> m_IBO;
			std::unique_ptr<Shader> m_Shader;
			std::unique_ptr<Renderer> m_Renderer;

			void onUpdate(float deltaTime) override;
			void onRender() override;
			void onImGuiRender() override;

		private:
			float m_clearColor[4];
		};
	}
}

