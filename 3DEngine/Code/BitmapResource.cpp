#include "BitmapResource.h"
#include <Windows.h>
#include <iostream>
#include "Logger.h"
#include <sstream>

BitmapResource::BitmapResource(char* path)
{
	pixelData = NULL;
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
		Logger::getInstance().log(CRITICAL, "Geen BMP gevonden.");
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
	int width = bm.bmWidth;
	int height = bm.bmHeight;
	std::stringstream sstm;
	sstm << "width:" << width << " Height:" << height;
	Logger::getInstance().log(INFO, sstm.str());

	//Create an array to hold all the heightdata
	//WHY is a BYTE array used, and not e.g. a INT array?
	//WHY "*3"?
	pixelData = new BYTE[width*height * 3];

	//Iterate through the BMP-file and fill the heightdata-array
	for (int lHeight = 0; lHeight < height; lHeight++)
	{
		for (int lWidth = 0; lWidth < width; lWidth++)
		{
			pixelData[(lHeight*width * 3) + lWidth * 3 + 0] = GetRValue(GetPixel(lhdcDest, lWidth, lHeight));
			pixelData[(lHeight*width * 3) + lWidth * 3 + 1] = GetGValue(GetPixel(lhdcDest, lWidth, lHeight));
			pixelData[(lHeight*width * 3) + lWidth * 3 + 2] = GetBValue(GetPixel(lhdcDest, lWidth, lHeight));
		}
	}

	for (int i = 0; i < width*height * 3; i += 3)
	{
		static int x = 0;
		int test = pixelData[i + 0];
		int test2 = pixelData[i + 1];
		int test3 = pixelData[i + 2];
		x++;

		std::stringstream sstm;
		sstm << "Pixel: " << x << " R: " << test << " G: " << test2 << " B: " << test3;

		Logger::getInstance().log(INFO, sstm.str());
	}
	//How to optimize this function? (hint: heightmaps are grayscale BMP's)
}


BitmapResource::~BitmapResource()
{
}
