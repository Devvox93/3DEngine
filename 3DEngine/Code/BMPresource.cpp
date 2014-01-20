#include "BMPresource.h"
#include <Windows.h>
#include <iostream>
#include "Logger.h"
#include <sstream>
#include <string>

BMPresource::BMPresource(std::string path)
{
	HANDLE hbmp;	//Handle to an object (standard handle)
	HDC lhdcDest;	//Handle to Device Context (Windows GDI)

	//Create a memory device context compatible with the specified device (NULL)
	lhdcDest = CreateCompatibleDC(NULL);
	if (lhdcDest == NULL)
	{
		DeleteDC(lhdcDest);	//Delete the DC (prevents a memory leak!)
		return;		//Jump out of the function
	}

	//Windows GDI load image of type BMP (fileformat)
	hbmp = LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hbmp == NULL)	//Give a visual warning if the loading of the image failed
	{
		Logger::getInstance().log(WARNING, "Could not load BMP from path: " + std::string(path));
		DeleteDC(lhdcDest);
		isLoaded = false;
		return;		//Jump out of the function
	}
	//At this point it is sure that lhdcDest & hbmp are valid.
	//Load the bmp into the device context (memory space)
	SelectObject(lhdcDest, hbmp);
	//The BITMAP structure defines the type, width, height, color format, and bit values of a bitmap
	isLoaded = true;
};

BMPresource::~BMPresource()
{
};