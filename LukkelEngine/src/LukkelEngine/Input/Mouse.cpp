#include "LKpch.h"
#include "LukkelEngine/Input/Mouse.h"
#include "LukkelEngine/Core/Application.h"

namespace LukkelEngine {

	// FIXME
	bool Mouse::isButtonPressed(MouseCode button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().getGLFWWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Mouse::getMousePosition()
	{
		double xpos, ypos;
		glfwGetCursorPos(Application::get().getGLFWWindow(), &xpos, &ypos); // CIRCULAR DEPENDENCY
		float x = static_cast<float>(xpos);
		float y = static_cast<float>(ypos);
		return std::make_pair(x, y);
	}

}
