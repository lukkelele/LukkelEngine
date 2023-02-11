#include "LukkelEngine/Input/Mouse.h"

namespace LukkelEngine {

	bool Mouse::isButtonPressed(MouseCode button)
	{
		return false;
	}

	glm::vec2 Mouse::getMousePosition()
	{
		return glm::vec2(0, 0); // for now
	}

	float Mouse::getMouseX()
	{
		return 0.0f;
	}
	
	float Mouse::getMouseY()
	{
		return 0.0f;
	}

}
