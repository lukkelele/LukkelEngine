#pragma once

#include <vector> // FIXME
#include "LukkelEngine/Test/Test.h"
#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/VertexBufferLayout.h"
#include "LukkelEngine/Renderer/VertexBuffer.h"
#include "LukkelEngine/Renderer/IndexBuffer.h"
#include "LukkelEngine/Renderer/Texture.h"
#include "LukkelEngine/Renderer/Shader.h"


namespace LukkelEngine {
	namespace test {

		class TestDrawTriangle2 : public Test
		{
		public:
			TestDrawTriangle2();
			~TestDrawTriangle2();

			std::unique_ptr<VertexArray> m_VAO;
			std::unique_ptr<VertexBuffer> m_VBO;
			std::unique_ptr<IndexBuffer> m_IBO;
			std::unique_ptr<Shader> m_Shader;
			std::unique_ptr<Renderer> m_Renderer;

			void onUpdate(float deltaTime) override;
			void onRender() override;
			void onImGuiRender() override;

		private:
		};
	}
}

