#pragma once
#include <Test/Test.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Shader.h>
#include <Renderer.h>

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

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
		
	private:
	};
}
