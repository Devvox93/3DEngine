#include "Terrain.h"
#include <Windows.h>
#include <iostream>
#include "Logger.h"
#include <sstream>
#include <string>

Terrain::Terrain(std::string path, std::string texturePath, ResourceManager *resourceManager)
{
	data = new TerrainData();
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
	char* terrainPath = new char[path.length() + 1];
	strcpy_s(terrainPath, path.length() + 1, path.c_str());

	hbmp = LoadImage(NULL, terrainPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hbmp == NULL)	//Give a visual warning if the loading of the image failed
	{
		Logger::getInstance().log(WARNING, "Could not load BMP from path: " + std::string(path) + ", using hardcoded emergency terrain.");
		data->width = 2;
		data->height = 2;
		aTerrainVertices = new Vertex[getWidth() * getHeight()];
		aTerrainVertices[0] = { -1000.0f,//x
								0.0f,//y
								-1000.0f,//z
								0.0f,//u
								0.0f };//v
		aTerrainVertices[1] = { 1000.0f,
								0.0f,
								-1000.0f,
								1.0f,
								0.0f };
		aTerrainVertices[2] = { -1000.0f,
								0.0f,
								1000.0f,
								0.0f,
								1.0f };
		aTerrainVertices[3] = { 1000.0f,
								0.0f,
								1000.0f,
								1.0f,
								1.0f };
		amountOfIndices = 6;// 2 triangles on emergency terrain, good for 6 vertex indices.
		aTerrainIndices = new int[amountOfIndices];
		aTerrainIndices[0] = 0;
		aTerrainIndices[1] = 1;
		aTerrainIndices[2] = 2;
		aTerrainIndices[3] = 1;
		aTerrainIndices[4] = 2;
		aTerrainIndices[5] = 3;
		texture = resourceManager->getTexture(texturePath);
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
	aTerrainVertices = new Vertex[getWidth() * getHeight()];

	//Iterate through the BMP-file and fill the heightdata-array
	for (int lHeight = 0; lHeight < getHeight(); lHeight++)
	{
		for (int lWidth = 0; lWidth < getWidth(); lWidth++)
		{
			aTerrainVertices[(lHeight*getWidth()) + lWidth] = { -(getWidth() / 2) + (float)lWidth, //x
																-0.5f + ((float)GetRValue(GetPixel(lhdcDest, lWidth, lHeight)) / 255.0f), //y
																(getWidth() / 2) - (float)lHeight, //z
																(1.0f / (getWidth() - 1)) * lWidth, //u
																(1.0f / (getHeight() - 1)) * lHeight }; //v
		}
	}

	amountOfIndices = (getWidth() - 1) * (getHeight() - 1) * 2 * 3;// * 2 * 3 because there's 2 triangles with 3 vertices per square
	aTerrainIndices = new int[amountOfIndices];

	std::stringstream ss2;
	ss2 << "Amount of planes: " << amountOfIndices / 3 << std::endl << "Amount of vertices: " << getWidth() * getHeight() << std::endl << "Amount of indices: " << amountOfIndices << std::endl;
	ss2 << "Good for a total of " << ((amountOfIndices * sizeof(int) + (getWidth() * getHeight() * sizeof(Vertex)))) / 1024 << " kbytes.";
	Logger::getInstance().log(INFO, ss2.str());

	int offset = 0;
	for (int i = 0; i < amountOfIndices; i += 6)
	{
		if (i != 0 && i % ((getWidth() - 1) * 6) == 0)
		{
			offset += 1;
		}
		aTerrainIndices[i + 0] = i / 6 + offset;
		aTerrainIndices[i + 1] = i / 6 + getWidth() + offset;
		aTerrainIndices[i + 2] = i / 6 + 1 + offset;
		aTerrainIndices[i + 3] = i / 6 + 1 + offset;
		aTerrainIndices[i + 4] = i / 6 + getWidth() + offset;
		aTerrainIndices[i + 5] = i / 6 + getWidth() + 1 + offset;
	}
	texture = resourceManager->getTexture(texturePath);
};

Terrain::~Terrain()
{
	delete data;
	delete aTerrainVertices;
	delete aTerrainIndices;
};

int Terrain::getWidth()
{
	return data->width;
};

int Terrain::getHeight()
{
	return data->height;
};

Vertex* Terrain::getVertices()
{
	return aTerrainVertices;
};

int Terrain::getAmountOfIndices()
{
	return amountOfIndices;
};

int* Terrain::getIndices()
{
	return aTerrainIndices;
};

TextureResource* Terrain::getTextureResource()
{
	return texture;
};