#include <Test/TestKeyInput.h>

namespace test {

	TestKeyInput::TestKeyInput()
	{
		m_rotX = 0.0f;
		m_rotY = 0.0f;
		m_Window = glfwCreateWindow(400, 400, "Test Key Input", NULL, NULL);
		// GLCall(glfwMakeContextCurrent(m_Window));
	}

	TestKeyInput::TestKeyInput(GLFWwindow* window)
	{
		m_rotX = 0.0f;
		m_rotY = 0.0f;
	}

	TestKeyInput::~TestKeyInput(){}

	void TestKeyInput::SetWindow(GLFWwindow* window)
	{
		m_Window = glfwCreateWindow(400, 400, "Test Key Input", NULL, window);
	}

	void TestKeyInput::KeyInput(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		const float rotationSpeed = 5.0f;
		LOG(key);
		// actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			switch (key) {
			case GLFW_KEY_UP:
				m_rotX -= rotationSpeed;
				LOG("KEY_UP");
				break;
			case GLFW_KEY_DOWN:
				m_rotX += rotationSpeed;
				LOG("KEY_DOWN");
				break;
			case GLFW_KEY_RIGHT:
				m_rotY += rotationSpeed;
				LOG("KEY_RIGHT");
				break;
			case GLFW_KEY_LEFT:
				m_rotY -= rotationSpeed;
				LOG("KEY_LEFT");
				break;
			}
		}
	}

	void TestKeyInput::onRender()
	{
		int focused = glfwGetWindowAttrib(m_Window, GLFW_FOCUSED);
		if (glfwGetCurrentContext() == m_Window) {
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

			GLCall(glfwSwapBuffers(m_Window));
			GLCall(glfwPollEvents());
		}

	}
	void TestKeyInput::onImGuiRender()
	{
		ImGui::Text("Key input");
	}
	void TestKeyInput::onUpdate(float freq){}
}