#pragma once

#include <Test/Test.h>
#include <vector>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Shader.h>
#include <Renderer.h>
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
