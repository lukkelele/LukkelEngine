#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/* Tests */
#include <TestClearColor.h>
#include <TestTexture2D.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <Display.h>
#include <GLErrorHandler.h>
#include <Renderer.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <VertexArray.h>
#include <IndexBuffer.h>
#include <Shader.h>
#include <Texture.h>
#include <Mesh.h>

#define DEFAULT_GRAPHICS_MODE 1		// Default 3D
#define DEFAULT_BLENDING_MODE 1     // Blending enabled per default
#define GRAPHICS_MODE_3D      1
#define GRAPHICS_MODE_2D      0

class lukkelEngine
{
public:
	lukkelEngine();
	lukkelEngine(unsigned int mode);
	lukkelEngine(unsigned int mode, unsigned int blending);
	~lukkelEngine();


private:
	GLFWwindow* window;
	Renderer renderer;
	unsigned int graphicsMode;
	unsigned int blending; // 0 or 1
	int status;

	int init(unsigned int graphicsMode, unsigned int blending);
	void setMode(unsigned int setting);
	void setBlending(unsigned int setting);
	
};