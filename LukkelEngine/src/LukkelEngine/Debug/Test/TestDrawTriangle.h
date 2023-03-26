#pragma once
#include "LukkelEngine/Debug/Test/Test.h"
#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/VertexBufferLayout.h"
#include "LukkelEngine/Renderer/VertexBuffer.h"
#include "LukkelEngine/Renderer/IndexBuffer.h"
#include "LukkelEngine/Renderer/Texture.h"
#include "LukkelEngine/Renderer/Shader.h"


namespace LukkelEngine {

	namespace test {

		class TestDrawTriangle : public Test
		{
		public:
			TestDrawTriangle();
			~TestDrawTriangle();

			unsigned int m_VAO;
			unsigned int m_VBO;
			unsigned int m_VertexShader;
			unsigned int m_FragmentShader;
			unsigned int m_Shader;

			void OnUpdate(float deltaTime) override;
			void onRender() override;
			void OnImGuiRender() override;
		};

	}

}
