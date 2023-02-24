#pragma once

#include "LukkelEngine/Input/MouseCodes.h"
#include "glm/glm.hpp"

namespace LukkelEngine {

	class Mouse
	{
	public:
		static bool isButtonPressed(MouseCode button);
		static std::pair<float, float> getMousePosition();
	};

}