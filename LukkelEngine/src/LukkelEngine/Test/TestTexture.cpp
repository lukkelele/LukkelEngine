#include <Test/TestTexture.h>

namespace LukkelEngine {
	using namespace test;

	TestTexture::TestTexture()
	{
		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(rectangle, (sizeof(rectangle) / sizeof(float)) * sizeof(float));
		m_IBO = std::make_unique<IndexBuffer>(rect_indices, (sizeof(rect_indices) / sizeof(unsigned int)) * sizeof(unsigned int));
		VertexBufferLayout layout;
		layout.push<float>(2);
		layout.push<float>(2);

		m_VAO->addBuffer(*m_VBO, layout);
		m_Shader = std::make_unique<Shader>("res/shaders/default3D.shader");
		m_Texture = std::make_unique<Texture>("res/textures/tinder_logo.png");
		m_Shader->bind();
		m_Texture->bind();
		m_Shader->setUniform1i("u_Texture", 0);
		m_Renderer->draw(*m_VAO, *m_IBO, *m_Shader);
	}

	TestTexture::~TestTexture(){}

	void TestTexture::onRender()
	{
		m_Renderer->draw(*m_VAO, *m_IBO, *m_Shader);
	}

	void TestTexture::onImGuiRender() {}
	void TestTexture::onUpdate(float updateFreq){}
}
