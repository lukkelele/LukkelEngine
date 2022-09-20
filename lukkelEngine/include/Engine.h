#ifndef _ENGINE_H
#define _ENGINE_H
#include "../i"
#include <vector>
#include <GLFW/glfw3.h>
#include <fstream>
#include <strstream>
#include <algorithm>
#include <string>

using namespace std;

class Engine {

public:
    Engine();
    Engine(int width, int height);

public:
    GLFWwindow* window;
    struct vec2 { float u=0; float v=0; float w=1; };
    struct vec3 { float x=0; float y=0; float z=0; float w=1; };
    struct triangle
    {
		vec3 p[4];
		vec2 t[3];  // texture 
    };
    struct mesh
    {
        std::vector<triangle> tris;
    };
    struct mat4 { float m[4][4] = { 0 }; };



private:
    int height;
    int width;
    mesh meshCube;
    mat4 matProj;
	vec3 vCam;	    // Location of camera in world space
	vec3 vLookDir;	// Direction vector along the direction camera points
	float yaw;		// FPS Camera rotation in XZ plane
	float theta;	// Spins World transform

public:
    int initGLFW();
    int createWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
    bool onUserCreate();
    bool onUserUpdate(float elapsedTime);
    void clearScreen();
    void getScreenSize();
    void multiplyMatrix(vec3& a, vec3& b, mat4& mat);
    void drawLine(vec3 vec1, vec3 vec2); /* Draw a line from vec1 -> vec2 */
    float degreeToRadian(float degrees);
    float getAspectRatio();
    bool LoadFromObjectFile(std::string sFilename, bool bHasTexture = false);
    int getHeight();
    int getWidth();


};


#endif // _GRAPHICS_ENGINE_H