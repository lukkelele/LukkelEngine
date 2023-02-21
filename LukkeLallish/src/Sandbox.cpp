#include "LukkelEngine/Core/Application.h"
#include "TestLayer.h"


class Sandbox : public LukkelEngine::Application
{
public:
	Sandbox(const LukkelEngine::ApplicationDetails& details =  LukkelEngine::ApplicationDetails("Sandbox", 1920, 1080))
		: LukkelEngine::Application(details)
	{	
	}

	~Sandbox()
	{
	}

};

int main()
{
	using namespace LukkelEngine;
	Sandbox app;
	s_ptr<Scene>scene = std::make_shared<Scene>();
	app.setScene(scene);

	TestLayer layer;
	app.pushLayer(&layer); // heap bug at LayerStack destructor

	app.run();

	return 0;
}