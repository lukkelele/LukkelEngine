#include <LukkelEngine.h>


#define LOG(x) std::cout << "LOG: " << x << std::endl;


int main(void)
{
	Cube cube; // unit cube
	LukkelEngine Engine = LukkelEngine(GRAPHICS_MODE_2D, BLENDING_ENABLED);
	GLFWwindow* window = Engine.getWindow();

	// Create the test menu
	test::Test* currentTest = Engine.currentTest;
	test::TestMenu* testMenu = Engine.testMenu;
	currentTest = testMenu;		// open menu initially

	while (!glfwWindowShouldClose(window))
	{
		Engine.screenUpdate();
		Engine.testRunner(ZERO_UPDATE_FREQUENCY);
		Engine.render();
	}

    return 0;
}
