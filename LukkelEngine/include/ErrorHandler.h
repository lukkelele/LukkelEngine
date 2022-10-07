#pragma once

#include <GL/gl.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// TODO: Fix assertion on Linux
#define ASSERT(x) //if (!(x)) __debugbreak();
#define LCall(x) GLClearError(); x ; ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#define LOG(x) std::cout << x << std::endl;

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

