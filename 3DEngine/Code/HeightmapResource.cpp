#include "HeightmapResource.h"
#include <Windows.h>
#include <iostream>
#include "Logger.h"
#include <sstream>
#include <string>
#include <map>



HeightmapResource::HeightmapResource(char* path)
{
	data = new Heightmap();
	HDC lhdcDest;	//Handle to Device Context (Windows GDI)
	HANDLE hbmp;	//Handle to an object (standard handle)
	//HINSTANCE hInst;//Handle to an instance (instance of the window)

	//Create a memory device context compatible with the specified device (NULL)
	lhdcDest = CreateCompatibleDC(NULL);
	if (lhdcDest == NULL)
	{
		DeleteDC(lhdcDest);	//Delete the DC (prevents a memory leak!)
		return;		//Jump out of the function
	}

	//Windows GDI load image of type BMP (fileformat)
	hbmp = LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hbmp == NULL)	//Give a visual warning if the loading of the image failed
	{
		Logger::getInstance().log(WARNING, "Could not load BMP from path: " + std::string(path));
		return;		//Jump out of the function
	}
	//At this point it is sure that lhdcDest & hbmp are valid.
	//Load the bmp into the device context (memory space)
	SelectObject(lhdcDest, hbmp);
	//The BITMAP structure defines the type, width, height, color format, and bit values of a bitmap
	BITMAP bm;
	//The GetObject function retrieves information for the specified graphics object
	//bm is cast to a "void*" because GetObject function doesn't 'know' it's format 
	//(don't know what it is, but just put it in that buffer)
	GetObject(hbmp, sizeof(BITMAP), (void*)&bm);

	//Store the width and height of the heightmap
	data->width = bm.bmWidth;
	data->height = bm.bmHeight;

	//Create an array to hold all the heightdata
	data->pixelData = new BYTE[data->width*data->height];

	//Iterate through the BMP-file and fill the heightdata-array
	for (int lHeight = 0; lHeight < data->height; lHeight++)
	{
		for (int lWidth = 0; lWidth < data->width; lWidth++)
		{
			data->pixelData[(lHeight*data->width) + lWidth] = GetRValue(GetPixel(lhdcDest, lWidth, lHeight));
			/*std::stringstream ss;
			ss << "X: " << lWidth << " Y: " << lHeight << " Height: " << (int)GetRValue(GetPixel(lhdcDest, lWidth, lHeight));
			Logger::getInstance().log(INFO, ss.str());*/
		}
	}
	
	
	
}


HeightmapResource::~HeightmapResource()
{
}
