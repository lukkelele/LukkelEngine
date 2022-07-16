
#include "GraphicsEngine.h"


int main() {

	GraphicsEngine Engine = GraphicsEngine();
	Engine.createWindow(640, 480, "Lukkelele Game Engine", NULL, NULL);
	Engine.onUserUpdate(0);
	Engine.onUserCreate();

    /* Make the window's context current */
    glfwMakeContextCurrent(Engine.window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(Engine.window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(Engine.window);

        /* Poll for and process events */
        glfwPollEvents();
    }
	return 0;
}
