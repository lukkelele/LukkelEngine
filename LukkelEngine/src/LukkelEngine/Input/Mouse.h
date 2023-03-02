#pragma once

#include "LukkelEngine/Input/MouseCodes.h"
#include "glm/glm.hpp"

namespace LukkelEngine {

	class Mouse
	{
	public:
		// TODO: Static necessary?
		static bool isButtonPressed(MouseCode button);
		static std::pair<float, float> getMousePosition();
		static float Mouse::getMouseX();
		static float Mouse::getMouseY();

	};

}