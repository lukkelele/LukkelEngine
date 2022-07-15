#ifndef _GRAPHICS_ENGINE_H
#define _GRAPHICS_ENGINE_H
#include <vector>

#define Z_FAR 
#define Z_NEAR

class GraphicsEngine {

public:
	GraphicsEngine();

public:
	bool onUserCreate();
	bool onUserUpdate(float elapsedTime);
	void clearScreen();
	float getScreenSize();
	float getAspectRatio();
	

public:
	int width;
	int height;
	struct vec3d { float x, y, z; };
	struct triangle { vec3d p[3]; };
	struct mesh { std::vector<triangle> tris; };
	struct mat4x4 { float m[4][4] = { 0 }; };

private:
	mesh meshCube;
	GLFWvidmode* videoMode;
};



#endif // _GRAPHICS_ENGINE_H


