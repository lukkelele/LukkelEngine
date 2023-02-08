#include <LKpch.h>
#include <Test/TestDrawTriangle2.h>

namespace LukkelEngine {
	using namespace test;

	TestDrawTriangle2::TestDrawTriangle2()
	{
		// GLCall(glDisable(GL_DEPTH_TEST));
		float coordinates[6] = {
		   -1.0f, 0.0f,
			0.5f, 0.0f,
			0.3f, 0.5f
		};

		int indices[3] = {
			0, 1, 2
		};

		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(coordinates, 6 * sizeof(float));
		m_IBO = std::make_unique<IndexBuffer>(indices, 3);
		VertexBufferLayout layout;
		layout.push<float>(2);
		m_VAO->addBuffer(*m_VBO, layout);

		m_Shader = std::make_unique<Shader>("res/shaders/BasicTest.shader");
		m_Shader->bind();
		m_Renderer->draw(*m_VAO, *m_IBO, *m_Shader);
	}

	TestDrawTriangle2::~TestDrawTriangle2() {}

	void TestDrawTriangle2::onImGuiRender() {}

	void TestDrawTriangle2::onRender()
	{
		m_Renderer->draw(*m_VAO, *m_IBO, *m_Shader);
	}

	void TestDrawTriangle2::onUpdate(float deltaTime)
	{

	}
}
