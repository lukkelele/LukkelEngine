#pragma once
#include "LukkelEngine/Input/Keycodes.h"

#include <utility>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace LukkelEngine {

	class Keyboard
	{
	public:
		static bool IsKeyPressed(KeyCode key);
	};
}
