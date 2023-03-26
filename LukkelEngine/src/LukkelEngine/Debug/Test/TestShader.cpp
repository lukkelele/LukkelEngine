#include "LKpch.h"
#include "LukkelEngine/Debug/Test/TestShader.h"

namespace LukkelEngine {

	namespace test {

		TestShader::TestShader()
		{
			m_VAO = std::make_unique<VertexArray>();
			m_VBO = std::make_unique<VertexBuffer>(rectangle, 8 * sizeof(float));
			m_IBO = std::make_unique<IndexBuffer>(rect_indices, 3);
			VertexBufferLayout layout;
			layout.Push<float>(2);
			m_VAO->AddBuffer(*m_VBO, layout);

			m_Shader = std::make_unique<Shader>("assets/shaders/basic2.shader");
			m_Shader->Bind();
			m_Shader->SetUniform4f("u_Color", 0.5f, 0.1f, 0.5f, 1.0f);
		}

		TestShader::~TestShader(){}

		void TestShader::onRender()
		{
			if (c > 1.0f || c < 0.0f)
				inc = -inc;
			c += inc;

			m_Shader->Bind();
			m_Shader->SetUniform4f("u_Color", c, 0.35, c, 1.0);
			m_Renderer->Draw(*m_VAO, *m_IBO, *m_Shader);
		}

		void TestShader::OnImGuiRender(){}
		void TestShader::OnUpdate(float freq){}

	}

}

