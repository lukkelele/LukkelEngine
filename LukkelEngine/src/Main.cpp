#include <LukkelEngine/Core/Application.h>

int main()
{
	using namespace LukkelEngine;
	Application app;
	LK_CORE_INFO("Application created");
	app.run();

	return 0;
}
