#pragma once
#include <GL/glew.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

//#define ASSERT(x) if (!(x)) __debugbreak();
#define ASSERT(x) //if (!(x)) __debugbreak();
#define GLCall(x) GLClearError(); x ; ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#define LOG(x) std::cout << "LOG: " << x << std::endl;

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);