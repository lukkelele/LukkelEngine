#pragma once

#include <utility>

// #include "GL/glew.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "LukkelEngine/Input/Keycodes.h"

namespace LukkelEngine {

	class Keyboard
	{
	public:
		static bool isKeyPressed(KeyCode key);
	};
}
