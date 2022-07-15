#include <iostream>
#include <GLFW/glfw3.h>
#include "GraphicsEngine.h"


GraphicsEngine::GraphicsEngine() {
	
};

bool GraphicsEngine::onUserCreate() {
	meshCube.tris = {
		// South
		{ 0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f },
		// East
		{ 1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 0.0f,  1.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 1.0f },
		// North
		{ 1.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 1.0f,  0.0f, 0.0f, 0.0f },
		// West
		{ 0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 0.0f },
		// Top
		{ 0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 0.0f },
		// Bottom
		{ 0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f }
	};
	// PROJECTION MATRIX
	float f_near = 0.1f;
	float f_far = 1000.f;
	float f_fov = 90.f;
	//float f_aspectRatio = 

	return true;
}

bool GraphicsEngine::onUserUpdate(float elapsedTime) {

	clearScreen();

	return true;
}

void GraphicsEngine::clearScreen() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Only works when on window is on primary monitor
float GraphicsEngine::getScreenSize() {
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	this->height = mode->height;
	this->width = mode->width;
}
