#include <Display.h>


Display::Display(int width, int height, const char* title)
{
    glfwStatus = glfwInit();
    setVersion(MAJOR_VERSION, MINOR_VERSION);
    window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);    // Sync with monitor
    initGlew();
}

Display::Display(int width, int height, const char* title, unsigned int major_version, unsigned int minor_version)
{
    glfwStatus = glfwInit();
    setVersion(major_version, minor_version);
    window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);    // Sync with monitor
    initGlew();
}

GLFWwindow* initDisplay(int width, int height, const char* title, unsigned int major_version, unsigned int minor_version)
{
    int glfwStatus = glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);    // Sync with monitor
    glewInit();
    return window;
}

Display::Display()
{
    setVersion(MAJOR_VERSION, MINOR_VERSION);
}

Display::~Display()
{
	glfwTerminate();
}

int initGlew()
{
    GLCall(GLenum err = glewInit());
    if (err != GLEW_OK) {
        /* if error occured, print error message */
        printf("Error: %s\n", glewGetErrorString(err));
        return -1;
    }
    printf("openGL version: %s\n", glGetString(GL_VERSION)); /* output openGL version */
}

int Display::initGlew()
{
    GLCall(GLenum err = glewInit());
    if (err != GLEW_OK) {
        /* if error occured, print error message */
        printf("Error: %s\n", glewGetErrorString(err));
        return -1;
    }
    printf("openGL version: %s\n", glGetString(GL_VERSION)); /* output openGL version */
}

GLFWwindow* Display::getWindow()
{
    return window;
}

const char* Display::getTitle()
{
    return title;
}

bool Display::setVersion(unsigned int MAJOR, unsigned int MINOR)
{   // works
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR);
    return true;
}



