#include <iostream>
#include <string>
#include <sstream>
#include "Logger.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "BitmapLoader.h"



int main()
{
	Renderer *renderer = new Renderer();
	BitmapLoader *bmpManager = new BitmapLoader();
	bmpManager->LoadBMP("test.bmp");
	WindowManager *manager = new WindowManager();
	for (int i = 5; i > 0; --i)
	{
		manager->newWindow(renderer);
		
	}
	

	InputManager *iManager = new InputManager();

	while (manager->hasActiveWindow())
	{
		manager->updateWindows();

	}

	
	


	system("pause");
	return 0;

	
}