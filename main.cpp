#include "TestApp_1.h"


int main()
{
	TestApp_1 app{};
	if (!app.Init()) return EXIT_FAILURE;

	app.Run();

	return EXIT_SUCCESS;
}
