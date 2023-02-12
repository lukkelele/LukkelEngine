#include "LukkelEngine/Core/Application.h"
#include "TestLayer.h"


class Sandbox : public LukkelEngine::Application
{
public:
	Sandbox(const LukkelEngine::ApplicationDetails& details = LukkelEngine::ApplicationDetails())
		: LukkelEngine::Application(details)
	{	
		// m_Camera = LukkelEngine::create_u_ptr<LukkelEngine::Camera>();
	}

	~Sandbox()
	{
	}

};

int main()
{
	Sandbox app;
	LukkelEngine::ImGuiLayer imguiLayer;
	TestLayer layer;
	app.pushLayer(&layer); // heap bug at LayerStack destructor
	app.pushOverlay(&imguiLayer);

	app.run();

	return 0;
}