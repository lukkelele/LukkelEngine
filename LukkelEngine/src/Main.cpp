#include <LukkelEngine/Core/Application.h>

int main()
{
	using namespace LukkelEngine;
	Application app;
	LKLOG_TRACE("Application created");
	app.run();

	return 0;
}
