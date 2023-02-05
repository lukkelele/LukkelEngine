#pragma once

#include <GL/glew.h>
#include <Core/Log.h>

#include <stdint.h>
#include <cstring>
#include <memory>
#include <sstream>

/* TODO: Insert precompiled header */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

/* OpenGL error macro */
#define GLCall(x) GLClearError(); x ; LK_ASSERT(GLLogCall(#x, __FILE__, __LINE__))
/* Simple log functionality to terminal */
#define LOG(x) std::cout << "LOG: " << x << std::endl;

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);