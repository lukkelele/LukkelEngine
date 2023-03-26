#include "LKpch.h"
#include "LukkelEngine/Input/Mouse.h"
#include "LukkelEngine/Core/Application.h"

namespace LukkelEngine {

	// FIXME
	bool Mouse::IsButtonPressed(MouseCode button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetGLFWwindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	// TODO: Fix the getter for the GLFW window
	std::pair<float, float> Mouse::GetMousePosition()
	{
		double xpos, ypos;
		glfwGetCursorPos(Application::Get().GetGLFWwindow(), &xpos, &ypos);
		float x = static_cast<float>(xpos);
		float y = static_cast<float>(ypos);
		return std::make_pair(x, y);
	}

	float Mouse::GetMouseX()
	{
		auto [x, y] = GetMousePosition();
		return x;
	}

	float Mouse::GetMouseY()
	{
		auto [x, y] = GetMousePosition();
		return y;
	}

}
