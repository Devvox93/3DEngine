#include <iostream>
#include <string>
#include <sstream>
#include "Logger.h"
#include "WindowManager.h"
#include "Renderer.h"

int main()
{
	Renderer *renderer = new Renderer();
	WindowManager *manager = new WindowManager();
	for (int i = 5; i > 0; --i)
	{
		manager->newWindow(renderer);
	}
	while (manager->hasActiveWindow())
	{
		manager->updateWindows();
	}

	system("pause");
	return 0;
}