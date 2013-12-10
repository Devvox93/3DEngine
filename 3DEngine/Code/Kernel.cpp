#include <iostream>
#include <string>
#include <sstream>
#include "Logger.h"
#include "WindowManager.h"

int main()
{
	WindowManager *manager = new WindowManager();
	for (int i = 5; i > 0; --i)
	{
		manager->newWindow();
	}
	while (manager->hasActiveWindow())
	{
		manager->updateWindows();
	}

	system("pause");
	return 0;
}