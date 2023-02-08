#ifdef LK_USE_PRECOMPILED_HEADERS
	#include <LKpch.h>
#endif
#include <Input/Keyboard.h>

namespace LukkelEngine {

	Keyboard::Keyboard(){}

	Keyboard::~Keyboard(){}

	void Keyboard::bind(GLFWwindow* window)
	{
		GLCall(glfwSetWindowUserPointer(window, this));
		GLCall(glfwSetKeyCallback(window, input_static));
		GLCall(glfwSetInputMode(window, GLFW_STICKY_KEYS, 1));
	}

	void Keyboard::unbind(){}

	int Keyboard::keyPressed()
	{
		return 1;
	}

	void Keyboard::input(GLFWwindow* window, int key, int scanCode, int action, int mods)
	{
		// actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			switch (key) {
				/* ARROW KEYS */
				case Key::Up: {
					LOG("^");
					// m_RotX -= m_RotationSpeed;
					break;
				} case Key::Down: {
					LOG("v");
					// m_RotX += m_RotationSpeed;
					break;
				} case Key::Right: {
					LOG("->");
					// m_RotY += m_RotationSpeed;
					break;
				} case Key::Left: {
					LOG("<-");
					// m_RotY -= m_RotationSpeed;
					break;

				/* WASD */
				} case Key::W: {
					LOG("W");
					break;
				} case Key::A: {
					LOG("A");
					break;
				} case Key::S: {
					LOG("S");
					break;
				} case Key::D: {
					LOG("D");
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
