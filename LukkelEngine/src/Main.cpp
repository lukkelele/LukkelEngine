#include <LukkelEngine.h>
#include <Shader.h>

void KeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);

// Vertices coordinates
float vertices[] = { 
	-0.5f, 0.0f,  0.5f,
	-0.5f, 0.0f, -0.5f,
	 0.5f, 0.0f, -0.5f,
	 0.5f, 0.0f,  0.5f,
	 0.0f, 0.8f,  0.0f
};
// Indices for vertices order
int indices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};
float rectangle[] = {
	-0.5f, -0.5f,
	 0.5f, -0.5f,
	 0.5f,  0.5f,
	-0.5f,  0.5f
};
unsigned int rect_indices[]{
	0, 1, 2,
	2, 3, 0
};

float rotX = 0.0f;
float rotY = 0.0f;
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;

int main()
{
	LukkelEngine Engine = LukkelEngine(GRAPHICS_MODE_2D, BLENDING_ENABLED);
	GLFWwindow* window = Engine.GetWindow();
	// Create the test menu
	test::Test* currentTest = Engine.currentTest;
	test::TestMenu* testMenu = Engine.testMenu;
	currentTest = testMenu;		// open menu initially

	while (!glfwWindowShouldClose(window)) {
		Engine.ScreenUpdate();
		Engine.TestRunner(ZERO_UPDATE_FREQUENCY);
		Engine.Render();
	}

	return 0;
}




void KeyInput(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	const GLfloat rotationSpeed = 10;
	LOG(key);
	// actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch (key) {
		case GLFW_KEY_UP:
			rotX -= rotationSpeed;
			break;
		case GLFW_KEY_DOWN:
			rotX += rotationSpeed;
			break;
		case GLFW_KEY_RIGHT:
			rotY += rotationSpeed;
			break;
		case GLFW_KEY_LEFT:
			rotY -= rotationSpeed;
			break;
		}
	}
}

