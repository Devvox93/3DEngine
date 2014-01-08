#include "Ground.h"
#include <Windows.h>
#include <iostream>
#include "Logger.h"
#include <sstream>
#include <string>

Ground::Ground(char* path)
{
	data = new GroundData();
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
	aGroundVertices = new Vertex[data->width * data->height];

	//Iterate through the BMP-file and fill the heightdata-array
	for (int lHeight = 0; lHeight < data->height; lHeight++)
	{
		for (int lWidth = 0; lWidth < data->width; lWidth++)
		{
			aGroundVertices[(lHeight*data->width) + lWidth] = { -(data->width / 2) + (float)lWidth, //x
																-0.5 + ((float)GetRValue(GetPixel(lhdcDest, lWidth, lHeight)) / 255.0f), //y
																-(data->width / 2) + (float)lHeight, //z
																(1.0f / (data->width - 1)) * lWidth, //u
																(1.0f / (data->height - 1)) * lHeight }; //v
		}
	}

	amountOfIndices = (data->width - 1) * (data->height - 1) * 2 * 3;
	aGroundIndices = new int[amountOfIndices];

	std::stringstream ss2;
	ss2 << "Amount of planes: " << amountOfIndices / 3 << std::endl << "Amount of vertices: " << data->width * data->height << std::endl << "Amount of indices: " << amountOfIndices << std::endl;
	ss2 << "Good for a total of " << ((amountOfIndices * sizeof(int) + (data->width * data->height * sizeof(Vertex)))) / 1024 << " kbytes.";
	Logger::getInstance().log(INFO, ss2.str());

	int offset = 0;
	for (int i = 0; i < amountOfIndices; i += 6)
	{
		if (i != 0 && (i - 0) % ((data->width - 1) * 6) == 0)
		{
			offset += 1;
		}
		aGroundIndices[i + 0] = i / 6 + offset;
		aGroundIndices[i + 1] = i / 6 + 1 + offset;
		aGroundIndices[i + 2] = i / 6 + data->width + offset;
		aGroundIndices[i + 3] = i / 6 + 1 + offset;
		aGroundIndices[i + 4] = i / 6 + data->width + offset;
		aGroundIndices[i + 5] = i / 6 + data->width + 1 + offset;
	}
}


Ground::~Ground()
{
}
