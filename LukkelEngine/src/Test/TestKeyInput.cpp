#include <Test/TestKeyInput.h>

namespace test {

	TestKeyInput::TestKeyInput()
	{
		m_rotX = 0.0f;
		m_rotY = 0.0f;
		// m_Window = std::make_unique<GLFWwindow*>();
	}

	TestKeyInput::~TestKeyInput(){}

	void TestKeyInput::SetWindow(GLFWwindow& window)
	{
		LOG("Setting window (TestKeyInput)...");
		m_Window = std::make_unique<GLFWwindow*>(&window);
	}

	void TestKeyInput::KeyInput(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		LOG(key);
		// actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			switch (key) {
			case GLFW_KEY_UP:
				m_rotX -= m_RotationSpeed;
				LOG("KEY_UP");
				break;
			case GLFW_KEY_DOWN:
				m_rotX += m_RotationSpeed;
				LOG("KEY_DOWN");
				break;
			case GLFW_KEY_RIGHT:
				m_rotY += m_RotationSpeed;
				LOG("KEY_RIGHT");
				break;
			case GLFW_KEY_LEFT:
				m_rotY -= m_RotationSpeed;
				LOG("KEY_LEFT");
				break;
			}
		}
	}

	void TestKeyInput::onRender()
	{

	}
	void TestKeyInput::onImGuiRender()
	{
		ImGui::Text("Key input");
	}
	void TestKeyInput::onUpdate(float freq){}
}