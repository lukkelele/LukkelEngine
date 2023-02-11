#include <Input/Keyboard.h>

namespace LukkelEngine {

	Keyboard::Keyboard(){}

	void Keyboard::bindWindow(GLFWwindow* window)
	{
		glfwSetKeyCallback(window, input_static);
		glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
	}

	void Keyboard::unbindWindow(){}

	void Keyboard::bindCamera(Camera* camera)
	{
		m_Camera = create_u_ptr<Camera>(camera);
	}

	void Keyboard::unbindCamera(){}

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
					break;
				} case Key::Down: {

					break;
				} case Key::Right: {

					break;
				} case Key::Left: {

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
