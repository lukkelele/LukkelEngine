#include "LukkelEngine/Core/Application.h"
#include "TestLayer.h"


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
	TestLayer layer;

	app.pushLayer(&layer);

	LKLOG_CRITICAL("SANDBOX terminated!");
	return 0;
}