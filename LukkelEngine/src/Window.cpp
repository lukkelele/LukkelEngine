#include <Window.h>


Window::Window()
{
    m_Width =  DEFAULT_WIDTH;
    m_Height = DEFAULT_HEIGHT;
    m_Title =  DEFAULT_TITLE;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, DEFAULT_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, DEFAULT_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
    glfwMakeContextCurrent(m_Window);

    printf("GLFW version %s\n", glfwGetVersionString()); // add Debug flag
}

Window::Window(unsigned int width, unsigned int height, const char* title, unsigned int majorVersion, unsigned int minorVersion)
{
    m_Width = width;
    m_Height = height;
    if (title == NULL)
        title = DEFAULT_TITLE;
    m_Title = title;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
    //glfwMakeContextCurrent(m_Window);
    
    printf("GLFW version %s\n", glfwGetVersionString()); // add Debug flag
}
    

Window::~Window()
{
   glfwTerminate(); 
}

int Window::setVersion(unsigned int majorVersion, unsigned int minorVersion)
{
    // TODO: Add error handling to return 0 or -1 depending on outcome
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    return 1;
}

