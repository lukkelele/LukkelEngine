#ifndef _GL_ERROR_HANDLER_H
#define _GL_ERROR_HANDLER_H

#include <GL/glew.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError(); x ; ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

#endif /* _GL_ERROR_HANDLER_H */
