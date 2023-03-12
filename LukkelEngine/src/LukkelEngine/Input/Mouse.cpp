#include "LKpch.h"
#include "LukkelEngine/Input/Mouse.h"
#include "LukkelEngine/Core/Application.h"

namespace LukkelEngine {

	// FIXME
	bool Mouse::isButtonPressed(MouseCode button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().getGLFWwindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	// TODO: Fix the getter for the GLFW window
	std::pair<float, float> Mouse::getMousePosition()
	{
		double xpos, ypos;
		glfwGetCursorPos(Application::get().getGLFWwindow(), &xpos, &ypos);
		float x = static_cast<float>(xpos);
		float y = static_cast<float>(ypos);
		return std::make_pair(x, y);
	}

	float Mouse::getMouseX()
	{
		auto [x, y] = getMousePosition();
		return x;
	}

	float Mouse::getMouseY()
	{
		auto [x, y] = getMousePosition();
		return y;
	}

}
