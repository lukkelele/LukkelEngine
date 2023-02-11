#ifndef _LK_KEYBOARD_H
#define _LK_KEYBOARD_H

#include <LukkelEngine/Core/LKErrorHandler.h>
#include <glfw/glfw3.h>
#include <Input/Keycodes.h>

namespace LukkelEngine {

	class Keyboard
	{
	private:
		float m_RotX = 0;
		float m_RotY = 0;
		float m_RotationSpeed = 5.0f;
		GLFWwindow* m_WindowReference = nullptr;

	public:
		Keyboard();
		Keyboard(GLFWwindow* window);
		~Keyboard();

		void bind(GLFWwindow* window);
		void unbind();

		int keyPressed();
		void input(GLFWwindow* window, int key, int scanCode, int action, int mods);
		static void input_static(GLFWwindow* window, int key, int scanCode, int action, int mods);
	};
}
#endif /* _LK_KEYBOARD_H */
