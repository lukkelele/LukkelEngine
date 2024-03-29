#include "LKpch.h"
#include "LukkelEngine/Input/Keyboard.h"
#include "LukkelEngine/Core/Application.h" // Include here to avoid circular dependency

namespace LukkelEngine {

	/* Check to see if a key is pressed */
	bool Keyboard::IsKeyPressed(KeyCode key)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetGLFWwindow());
		int keyState = glfwGetKey(window, static_cast<int32_t>(key));
		return keyState == GLFW_PRESS;
	}

}
