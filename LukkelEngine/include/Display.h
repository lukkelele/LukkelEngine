#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <Renderer.h>
#include <gl/glew.h>
#include <GLFW/glfw3.h>

#define WIDTH  1600
#define HEIGHT 1024
#define TITLE  "lukkelEngine"
#define MAJOR_VERSION 3
#define MINOR_VERSION 3

/*
=================================================
DEPRECATED 
NOT TO BE USED!
=================================================
*/

class Display
{
public:
	Display(int width, int height, const char* title);
	Display(int width, int height, const char* title, unsigned int major_version, unsigned int minor_version);
	Display();
	~Display();

	GLFWwindow* window;
	
	GLFWwindow* getWindow();
	const char* getTitle();
	bool setVersion(unsigned int MAJOR, unsigned int MINOR);
	int initGlew();

	GLFWwindow* initDisplay();

private:
	int glfwStatus;
	int width;
	int height;
	const char* title;

};

int initGlew();
bool setVersion(unsigned int MAJOR, unsigned int MINOR);
const char* getTitle();

GLFWwindow* initDisplay(int width, int height, const char* title, unsigned int major_version, unsigned int minor_version);
GLFWwindow* getWindow();

#endif _DISPLAY_H  /* _DISPLAY_H */