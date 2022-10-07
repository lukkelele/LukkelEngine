#include <Window.h>


Window::Window()
{
    m_Width =  DEFAULT_WIDTH;
    m_Height = DEFAULT_HEIGHT;
    m_Title =  DEFAULT_TITLE;
     
}

Window::Window(unsigned int width, unsigned int height, const char* title)
{
    m_Width = width;
    m_Height = height;
    m_Title = title;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //TODO: set version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwMakeContextCurrent(m_Window);

    printf("GLFW version %s\n", glfwGetVersionString());
    
}
    

Window::~Window()
{
    
}
