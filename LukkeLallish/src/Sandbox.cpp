#include "LukkelEngine/Core/Application.h"

#include "TestLayer.h"
#include "LukkelEngine/Scene/Entity.h"


class Sandbox : public LukkelEngine::Application
{
public:
	Sandbox(const LukkelEngine::ApplicationDetails& details =  LukkelEngine::ApplicationDetails("Sandbox", 2340, 1200))
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

	// This will later be added in application as a 'New' scene button or just loading an old one
	s_ptr<Scene>scene = std::make_shared<Scene>();
	app.SetScene(scene);

	TestLayer layer;
	app.PushLayer(&layer);

	app.Run();

	return 0;
}