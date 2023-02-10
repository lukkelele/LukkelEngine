#include "LukkelEngine/Core/Application.h"
#include "TestLayer.h"
// #include "TestCoordinates.h"


class Sandbox : public LukkelEngine::Application
{
public:
	Sandbox(const LukkelEngine::ApplicationDetails& details = LukkelEngine::ApplicationDetails())
		: LukkelEngine::Application(details)
	{
	}

	~Sandbox()
	{
	}

};

int main()
{
	std::cout << "Hello World!" << std::endl;
	Sandbox app;
	GLFWwindow* window = app.getWindow();
	glEnable(GL_DEPTH_TEST);
	TestLayer layer;
	LKLOG_WARN("Pushing new layer");
	app.pushLayer(&layer); // heap bug at LayerStack destructor


	while (!glfwWindowShouldClose(window))
	{
		app.onUpdate();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	

	LKLOG_CRITICAL("SANDBOX terminated!");
	return 0;
}