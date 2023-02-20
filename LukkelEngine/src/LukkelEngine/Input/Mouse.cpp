#include "LukkelEngine/Input/Mouse.h"
#include "LukkelEngine/Core/Application.h"

namespace LukkelEngine {

	// FIXME
	bool Mouse::isButtonPressed(MouseCode button)
	{
		return false;
	}

	std::pair<float, float> Mouse::getMousePosition()
	{
		double xpos, ypos;
		glfwGetCursorPos(Application::get().getWindow(), &xpos, &ypos);
		float x = static_cast<float>(xpos);
		float y = static_cast<float>(ypos);
		return std::make_pair(x, y);
	}

}
