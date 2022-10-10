#include <LukkelEngine.h>
#include <Window.h>

#define WIDTH  800
#define HEIGHT 600

int main()
{
    //LOG("Starting LukkelEngine");    
    glfwInit();
    Window Window(WIDTH, HEIGHT, "LukkelEngine", 4, 3);
    glfwMakeContextCurrent(Window.m_Window);    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "Failed to init GLAD\n");
        return 1;
    }

    printf("OpenGL version: %s\n", glGetString(GL_VERSION));
    
    glViewport(0, 0, WIDTH, HEIGHT);

    while (!glfwWindowShouldClose(Window.m_Window))
    {
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the screen buffers
        glfwSwapBuffers(Window.m_Window);
    }

    // Terminates GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}
