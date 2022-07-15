#ifndef _GRAPHICS_ENGINE_H
#define _GRAPHICS_ENGINE_H
#include <vector>

class GraphicsEngine {

public:
	GraphicsEngine();

public:
	bool onUserCreate();
	bool onUserUpdate(float elapsedTime);
	void clearScreen();

public:
	struct vec3d { float x, y, z; };
	struct triangle { vec3d p[3]; };
	struct mesh { std::vector<triangle> tris; };

private:
	mesh meshCube;

};



#endif // _GRAPHICS_ENGINE_H


