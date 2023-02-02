#include <Input/Keyboard.h>


Keyboard::Keyboard()
{

}

Keyboard::~Keyboard(){}

void Keyboard::Bind(GLFWwindow* window)
{
	// GLCall(glfwSetWindowUserPointer(m_WindowReference, this));
	// GLCall(glfwSetKeyCallback(m_WindowReference, Input_static));
	GLCall(glfwSetWindowUserPointer(window, this));
	GLCall(glfwSetKeyCallback(window, Input_static));
}

void Keyboard::Unbind(){}

int Keyboard::KeyPressed()
{
	return 1;
}

void Keyboard::Input(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	LOG(key);
	// actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch (key) {
		case GLFW_KEY_UP:
			m_RotX -= m_RotationSpeed;
			break;
		case GLFW_KEY_DOWN:
			m_RotX += m_RotationSpeed;
			break;
		case GLFW_KEY_RIGHT:
			m_RotY += m_RotationSpeed;
			break;
		case GLFW_KEY_LEFT:
			m_RotY -= m_RotationSpeed;
			break;
		}
	}
}

void Keyboard::Input_static(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	Keyboard* Keyboard_ptr = static_cast<Keyboard*>(glfwGetWindowUserPointer(window));
	Keyboard_ptr->Input(window, key, scanCode, action, mods);
}

