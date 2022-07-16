#include <iostream>
#include <GLFW/glfw3.h>
#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine() {
	this->height = 0;
	this->width = 0;
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
	float z_near = 0.1f;
	float z_far = 1000.f;
	float fov = 90.f;
	float aspectRatio = getAspectRatio();
	float fovRad = degreeToRadian(fov);
	float fovRadian = 1.0f / tanf(fovRad * 0.5f); // might reuse fovRad here
	// matProj.m[ROW][COLUMN]
	matProj.m[0][0] = aspectRatio * fovRadian;
	matProj.m[1][1] = fovRadian;
	matProj.m[2][2] = z_far / (z_far - z_near);
	matProj.m[2][3] = 1.0f;
	matProj.m[3][2] = -(z_far * z_near) / (z_far - z_near);
	matProj.m[3][3] = 0.0f;

	return true;
}


float GraphicsEngine::degreeToRadian(float degrees) {
	// 180 degrees = 1 rad --> 1 degree = 1/180 rad
	return degrees * (1 / 180.0f) * 3.14f;
}

bool GraphicsEngine::onUserUpdate(float elapsedTime) {
	clearScreen();
	
	for (auto tri : meshCube.tris) {
		triangle triProj;
		for (int i = 0; i < 3; i++) {
			multiplyMatrix(tri.p[i], triProj.p[i], matProj);
		}
	}

	return true;
}


/* Matrix multiplication -> a*mat = b
   Input vector: a 
   Output vector: b  */
void GraphicsEngine::multiplyMatrix(vec3d& a, vec3d& b, mat4x4& mat) {
	b.x = a.x * mat.m[0][0] + a.y * mat.m[1][0] + a.z * mat.m[2][0] + mat.m[3][0];
	b.y = a.x * mat.m[0][1] + a.y * mat.m[1][1] + a.z * mat.m[2][1] + mat.m[3][1];
	b.z = a.x * mat.m[0][2] + a.y * mat.m[1][2] + a.z * mat.m[2][2] + mat.m[3][2];
	float w = a.x * mat.m[0][3] + a.y * mat.m[1][3] + a.z * mat.m[2][3] + mat.m[3][3];
	// Fourth element needs to be set to 1 to get back to 3D, divide xyz with w
	if (w != 0.0f) { b.x /= w; b.y /= w; b.z /= w; }
}


void GraphicsEngine::clearScreen() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Only works when on window is on primary monitor
void GraphicsEngine::getScreenSize() {
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	this->height = mode->height;
	this->width = mode->width;
}

float GraphicsEngine::getAspectRatio() {
	getScreenSize();
	return this->height / this->width;
}

/* Draw a line from vec1 -> vec2 */
void GraphicsEngine::drawLine(vec3d vec1, vec3d vec2) {
	std::vector<float> vertices = {
		vec1.x, vec1.y, vec1.z,
		vec2.x, vec2.y, vec2.z
	};
	// DRAW LINE
}
