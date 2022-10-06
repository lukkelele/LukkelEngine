#include <TestTexture2D.h>

/*
	TEST FILE, 2D TEXTURES
*/

namespace test {

	Texture2D::Texture2D()
		: m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		  m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		  m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0)
	{

		float positions[] = {
			/* Vertex positions and texture coordinates in 2D */
			/* The .shader files has location 1 for the texture coordinates */
			 -50.0f, -50.0f, 0.0f, 0.0f,
			  50.0f, -50.0f, 1.0f, 0.0f,
			  50.0f,  50.0f, 1.0f, 1.0f,
			 -50.0f,  50.0f, 0.0f, 1.0f
		};

		unsigned int indices[] {
			0, 1, 2,
			2, 3, 0
		};

		Renderer renderer;

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
		m_Shader = std::make_unique<Shader>("res/shaders/basic.shader");
		m_Shader->bind();
		m_Shader->setUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
		m_Texture = std::make_unique<Texture>("res/textures/tinder_logo.png");
		m_Shader->setUniform1i("u_Texture", 0); // pass slot


	}

	Texture2D::~Texture2D()
	{

	}

	void Texture2D::onUpdate(float deltaTime)
	{

	}

	void Texture2D::onRender()
	{

		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;
		m_Texture->bind();

		{	// One operation
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->bind();
			m_Shader->setUniformMat4f("u_MVP", mvp); // pass matrices here
			renderer.draw(*m_VAO, *m_IBO, *m_Shader);
		}

		{   // Second operation
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->bind();
			m_Shader->setUniformMat4f("u_MVP", mvp); // pass matrices here
			renderer.draw(*m_VAO, *m_IBO, *m_Shader);
		}

	}

	void Texture2D::onImGuiRender()
	{
		/* Sliders and text */
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f); 
		ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}