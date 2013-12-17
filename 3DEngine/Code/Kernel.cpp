#include <iostream>
#include <string>
#include <sstream>
#include "Logger.h"
#include "WindowManager.h"
#include "BitmapLoader.h"



int main()
{
	
	
	WindowManager *wManager = new WindowManager();
	for (int i = 5; i > 0; --i)
	{
		wManager->newWindow();
	}
	while (wManager->hasActiveWindow())
	{
		wManager->updateWindows();
	}
	BitmapLoader *bmpManager = new BitmapLoader();
	bmpManager->loadBMP();
	
	

	system("pause");
	return 0;

	
}