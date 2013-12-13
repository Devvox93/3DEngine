#include <iostream>
#include <string>
#include <sstream>
#include "Logger.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "Renderer.h"

int main()
{
	InputManager *iManager = new InputManager();
	iManager->assignWindowToKeyboard(/* Geef Window hier mee!! */);
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