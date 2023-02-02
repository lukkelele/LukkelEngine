#include <Input/Keyboard.h>


Keyboard::Keyboard()
{

}

Keyboard::~Keyboard(){}

int Keyboard::keyPressed(){}

void Keyboard::keyInput(GLFWwindow* window, int key, int scanCode, int action, int mods)
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
