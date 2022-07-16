#ifndef _GRAPHICS_ENGINE_H
#define _GRAPHICS_ENGINE_H
#include <vector>


class GraphicsEngine {

public:
	GraphicsEngine();

public:
	struct vec3d { float x, y, z; };
	struct triangle { vec3d p[3]; };
	struct mesh { std::vector<triangle> tris; };
	struct mat4x4 { float m[4][4] = { 0 }; };

private:
	int height;
	int width;
	mesh meshCube;
	mat4x4 matProj;

public:
	bool onUserCreate();
	bool onUserUpdate(float elapsedTime);
	void clearScreen();
	void getScreenSize();
	void multiplyMatrix(vec3d& a, vec3d& b, mat4x4& mat);
	void drawLine(vec3d vec1, vec3d vec2); /* Draw a line from vec1 -> vec2 */
	float degreeToRadian(float degrees);
	float getAspectRatio();


};


#endif // _GRAPHICS_ENGINE_H


