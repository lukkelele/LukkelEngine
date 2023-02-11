#include "LukkelEngine/Core/Application.h"
#include "TestLayer.h"
// #include "TestCoordinates.h"


class Sandbox : public LukkelEngine::Application
{
public:
	Sandbox(const LukkelEngine::ApplicationDetails& details = LukkelEngine::ApplicationDetails())
		: LukkelEngine::Application(details)
	{	
		m_Keyboard = LukkelEngine::create_u_ptr<LukkelEngine::Keyboard>();
		m_Keyboard->bind(m_Window->getWindow());

	}

	~Sandbox()
	{
	}

};

int main()
{
	Sandbox app;

	TestLayer layer;
	app.pushLayer(&layer); // heap bug at LayerStack destructor

	app.run();

	return 0;
}