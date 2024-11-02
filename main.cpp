#include "TestApp_2.h"


int main()
{
	TestApp_2 app{};
	if (!app.Init()) return EXIT_FAILURE;

	app.Run();

	return EXIT_SUCCESS;
}
