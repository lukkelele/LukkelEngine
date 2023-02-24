#pragma once

#include "GL/glew.h"
#include "LukkelEngine/Core/Base.h"

#include <stdint.h>
#include <cstring>
#include <fstream>

/* OpenGL error macro */
#define GLCall(x) GLClearError(); x ; LK_ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
