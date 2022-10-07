#pragma once

#include <ErrorHandler.h> 
#include <GLFW/glfw3.h>

#define DEFAULT_WIDTH   1024
#define DEFAULT_HEIGHT  768
#define DEFAULT_TITLE   "LukkelEngine"

#define DEFAULT_VERSION_MAJOR   4
#define DEFAULT_VERSION_MINOR   3

class Window
{
public:
    Window();
    Window(unsigned int width, unsigned int height, const char* title);
    ~Window();

    GLFWwindow*  m_Window;

    int createWindow();  /* Default settings */
    int createWindow(unsigned int width, unsigned int height, const char* title);
    int setVersion(unsigned int major, unsigned int minor);

private:

    unsigned int m_Width;
    unsigned int m_Height;
    const char*  m_Title;

};
