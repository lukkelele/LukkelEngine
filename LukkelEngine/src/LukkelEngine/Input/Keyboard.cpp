#include <Input/Keyboard.h>

namespace LukkelEngine {

	Keyboard::Keyboard(){}

	Keyboard::~Keyboard(){}

	void Keyboard::bind(GLFWwindow* window)
	{
		glfwSetKeyCallback(window, input_static);
		glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
	}

	void Keyboard::unbind(){}

	int Keyboard::keyPressed()
	{
		return 1;
	}

	void Keyboard::input(GLFWwindow* window, int key, int scanCode, int action, int mods)
	{
		// actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
		LKLOG_BLUE("keyPress: {0}", key);
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			switch (key) {
				/* ARROW KEYS */
				case Key::Up: {

					// m_RotX -= m_RotationSpeed;
					break;
				} case Key::Down: {

					// m_RotX += m_RotationSpeed;
					break;
				} case Key::Right: {

					// m_RotY += m_RotationSpeed;
					break;
				} case Key::Left: {

					// m_RotY -= m_RotationSpeed;
					break;

				/* WASD */
				} case Key::W: {

					break;
				} case Key::A: {

					break;
				} case Key::S: {

					break;
				} case Key::D: {

					break;
				}

			}
		}
	}

	void Keyboard::input_static(GLFWwindow* window, int key, int scanCode, int action, int mods)
	{
		Keyboard* Keyboard_ptr = static_cast<Keyboard*>(glfwGetWindowUserPointer(window));
		Keyboard_ptr->input(window, key, scanCode, action, mods);
	}

}
