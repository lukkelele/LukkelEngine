// #include <LukkelEngine/Core/Application.h>
// #include <LukkelEngine/Core/Log.h>
// #include <LukkelEngine/Renderer/Renderer.h>
/* FIX IMPORTS FOR Application file*/
#include <LukkelEngine/LukkelEngine.h>

/*
int main()
{
	LukkelEngine::LukkelEngine Engine = LukkelEngine::LukkelEngine();
	Engine.init();
	GLFWwindow* window = Engine.getWindow();
	// Create the test menu
	LukkelEngine::test::Test* currentTest = Engine.currentTest;
	LukkelEngine::test::TestMenu* testMenu = Engine.testMenu;
	currentTest = testMenu;	// open menu initially

	LukkelEngine::WindowResizeEvent e(1600, 1024);
	// LK_TRACE(e);

	while (!glfwWindowShouldClose(window)) {
		Engine.screenUpdate();
		Engine.testRunner(ZERO_UPDATE_FREQUENCY);
		Engine.render();
	}
	return 0;
}
*/
