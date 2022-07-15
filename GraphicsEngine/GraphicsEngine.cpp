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

