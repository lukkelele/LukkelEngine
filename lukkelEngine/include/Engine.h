#ifndef _ENGINE_H
#define _ENGINE_H
#include <vector>
#include <GLFW/glfw3.h>


class Engine {

public:
    Engine();
    Engine(int width, int height);

public:
    GLFWwindow* window;
    //    olc::PixelGameEngine olcEngine;
    struct vec3 { float x, y, z; };
    struct triangle { vec3 p[3]; };
    struct mesh { std::vector<triangle> tris; };
    struct mat4 { float m[4][4] = { 0 }; };

private:
    int height;
    int width;
    mesh meshCube;
    mat4 matProj;

public:
    int initGLFW();
    //    int initOLC();
    int createWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
    bool onUserCreate();
    bool onUserUpdate(float elapsedTime);
    void clearScreen();
    void getScreenSize();
    void multiplyMatrix(vec3& a, vec3& b, mat4& mat);
    void drawLine(vec3 vec1, vec3 vec2); /* Draw a line from vec1 -> vec2 */
    float degreeToRadian(float degrees);
    float getAspectRatio();
    bool createCube();


};


#endif // _GRAPHICS_ENGINE_H