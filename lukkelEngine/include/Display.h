#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <Renderer.h>
#include <gl/glew.h>
#include <GLFW/glfw3.h>

#define WIDTH  1600
#define HEIGHT 1024
#define TITLE  "Lukkelele"
#define MAJOR_VERSION 3
#define MINOR_VERSION 3

class Display
{
public:
	Display(int width, int height, const char* title);
	Display(int width, int height, const char* title, unsigned int major_version, unsigned int minor_version);
	Display();
	~Display();

	GLFWwindow* getWindow();
	const char* getTitle();

private:
	int glfwStatus;
	int width;
	int height;
	const char* title;
	GLFWwindow* window;

	int initGlew();
	bool setVersion(unsigned int MAJOR, unsigned int MINOR);
};

#endif _DISPLAY_H  /* _DISPLAY_H */