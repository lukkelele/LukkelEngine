#include "Engine.h"

class Sandbox {
	int main() {
		Engine engine = Engine(800, 600);
		while (!glfwWindowShouldClose(engine.window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			/* Swap front and back buffers */
			glfwSwapBuffers(engine.window);

			/* Poll for and process events */
			glfwPollEvents();
		}
		return 0;
	}
};