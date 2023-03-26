#pragma once

#include "LukkelEngine/Input/MouseCodes.h"
#include "glm/glm.hpp"

namespace LukkelEngine {

	class Mouse
	{
	public:
		static bool IsButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float Mouse::GetMouseX();
		static float Mouse::GetMouseY();

	};

}