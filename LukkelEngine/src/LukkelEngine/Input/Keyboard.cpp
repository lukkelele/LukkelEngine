#include <Input/Keyboard.h>

namespace LukkelEngine {

	Keyboard::Keyboard()
	{
		m_Position = { 0.0f, 0.0f, 0.0f };
		LKLOG_TRACE("CREATED -> pos -> (x,y,z) == ({0}, {1}, {2})", m_Position.x, m_Position.y, m_Position.z);
	}

	void Keyboard::bindWindow(GLFWwindow* window)
	{
		glfwSetKeyCallback(window, input_static);
		glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
	}

	void Keyboard::unbindWindow(){}

	int Keyboard::keyPressed() // FIXME
	{
		return 1;
	}

	void Keyboard::input(GLFWwindow* window, int key, int scanCode, int action, int mods)
	{
		// actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
		// LKLOG_BLUE("keyPress: {0}", key);
		LKLOG_TRACE("pos -> (x,y,z) == ({0}, {1}, {2})", m_Position.x, m_Position.y, m_Position.z);

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
					LKLOG_INFO("W");
					m_Position.x += 0.1f;
					m_Position.y += 0.1f;
					LKLOG_TRACE("pos -> (x,y,z) == ({0}, {1}, {2})", m_Position.x, m_Position.y, m_Position.z);
					break;
				} case Key::A: {

					break;
				} case Key::S: {
					LKLOG_INFO("S");
					m_Position.x -= 0.05f;
					m_Position.y -= 0.05f;
					LKLOG_TRACE("pos -> (x,y,z) == ({0}, {1}, {2})", m_Position.x, m_Position.y, m_Position.z);

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
