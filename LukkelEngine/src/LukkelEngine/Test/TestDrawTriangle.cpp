#include <Test/TestDrawTriangle.h>

namespace LukkelEngine {
	using namespace test;

	TestDrawTriangle::TestDrawTriangle()
	{
		GLCall(glDisable(GL_DEPTH_TEST));

		const char* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";
		
		const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(0.45f, 0.5f, 0.9f, 1.0f);\n"
			"}\n\0";

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, // left  
			 0.5f, -0.5f, 0.0f, // right 
			 0.0f,  0.5f, 0.0f  // top   
		};

		// Vertex shader
		m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(m_VertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(m_VertexShader);

		// Fragment shader
		m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(m_FragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(m_FragmentShader);

		// Link shaders
		m_Shader = glCreateProgram();
		glAttachShader(m_Shader, m_VertexShader);
		glAttachShader(m_Shader, m_FragmentShader);
		glLinkProgram(m_Shader);
		glDeleteShader(m_VertexShader);
		glDeleteShader(m_FragmentShader);
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	TestDrawTriangle::~TestDrawTriangle() {}

	void TestDrawTriangle::onImGuiRender()
	{

	}

	void TestDrawTriangle::onRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		glUseProgram(m_Shader);
		glBindVertexArray(m_VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void TestDrawTriangle::onUpdate(float deltaTime)
	{

	}

}