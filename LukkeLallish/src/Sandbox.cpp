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
	Sandbox app;

	TestLayer layer;
	LKLOG_TRACE("Pushing new layer");
	app.pushLayer(&layer); // heap bug at LayerStack destructor

	app.run();
	

	LKLOG_WARN("SANDBOX terminated!");
	return 0;
}