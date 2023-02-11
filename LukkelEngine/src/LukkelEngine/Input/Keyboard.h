#pragma once
#include "LukkelEngine/Core/LKErrorHandler.h"
#include "glfw/glfw3.h"
#include "LukkelEngine/Input/Keycodes.h"

namespace LukkelEngine {

	class Keyboard
	{
	private:
		GLFWwindow* m_WindowReference = nullptr;

	public:
		Keyboard();
		Keyboard(GLFWwindow* window);
		~Keyboard() = default;
		glm::vec3 m_Position;

		void bindWindow(GLFWwindow* window);
		void unbindWindow();

		int keyPressed();
		void input(GLFWwindow* window, int key, int scanCode, int action, int mods);
		static void input_static(GLFWwindow* window, int key, int scanCode, int action, int mods);
	};
}
