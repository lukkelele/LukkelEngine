#include "LukkelEngine/Test/TestTexture2D.h"

/*
	TEST FILE, 2D TEXTURES
*/

namespace LukkelEngine {
	using namespace test;

	TestTexture2D::TestTexture2D()
		: m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		  m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		  m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0)
	{
		GLCall(glDisable(GL_DEPTH_TEST));

		float positions[] = {
			/* Vertex positions and texture coordinates in 2D */
			/* The .shader files has location 1 for the texture coordinates (basic.shader) */
			 -50.0f, -50.0f, 0.0f, 0.0f,
			  50.0f, -50.0f, 1.0f, 0.0f,
			  50.0f,  50.0f, 1.0f, 1.0f,
			 -50.0f,  50.0f, 0.0f, 1.0f
		};

		unsigned int indices[] {
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4*4* sizeof(float));
		// Vertex Buffer layout
		VertexBufferLayout layout;
		layout.push<float>(2);
		layout.push<float>(2);

		m_VAO->addBuffer(*m_VertexBuffer, layout);
		m_IBO = std::make_unique<IndexBuffer>(indices, 6);

		// Shader creation
		m_Shader = std::make_unique<Shader>("assets/shaders/basic.shader"); // FIXME: Sandbox pathing
		m_Texture = std::make_unique<Texture>("assets/textures/tinder_logo.png"); // FIXME: Sandbox pathing
	}

	TestTexture2D::~TestTexture2D()
	{
		m_Shader->unbind();
	}

	void TestTexture2D::onUpdate(float deltaTime)
	{

	}

	void TestTexture2D::onRender()
	{
		m_Texture->bind();
		{	// One operation
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->bind();
			m_Shader->setUniformMat4f("u_MVP", mvp); // pass matrices here
			m_Renderer->draw(*m_VAO, *m_IBO, *m_Shader);
		}
		{   // Second operation
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->bind();
			m_Shader->setUniformMat4f("u_MVP", mvp); // pass matrices here
			m_Renderer->draw(*m_VAO, *m_IBO, *m_Shader);
		}

	}

	void TestTexture2D::onImGuiRender()
	{
		/* Sliders and text */
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f); 
		ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}