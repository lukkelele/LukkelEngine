#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// TODO: Fix the LCall macro with error assertion

//#define ASSERT(x) //if (!(x)) __debugbreak();
#define LCall(x); //GLClearError(); x ; ASSERT(GLLogCall(#x, __FILE__, __LINE__))
//#define LOG(x) std::cout << x << std::endl;


//void GLClearError()
//{
//    while (glGetError() != GL_NO_ERROR);
//}
//
//bool GLLogCall(const char* function, const char* file, int line)
//{
//    while (GLenum error = glGetError())
//    {
//        std::cout << "[OpenGL Error] (" << error << ")\nFUNCTION: " << function <<
//            "\nFILE: " << file << "\nLINE: " << line << std::endl;
//        return false;
//    }
//    return true;
//}
