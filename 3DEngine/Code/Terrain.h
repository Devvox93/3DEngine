/*
3D Engine
Xresource.h
Purpose: Loads X resources.

@author Patrick, Nick, Robert, Jordi
@version 1.0
*/

#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include "TextureResource.h"
#include "ResourceManager.h"
#include "Defines.h"

struct TerrainData
{
	int width;
	int height;
};

class Terrain
{
public:
	Terrain(char* path, char* texturepath, ResourceManager *resourceManager);
	~Terrain();
	int getWidth();
	int getHeight();
	Vertex* getVertices();
	int getAmountOfIndices();
	int* getIndices();
	TextureResource* getTextureResource();
private:
	TerrainData* data;
	Vertex* aTerrainVertices;
	int amountOfIndices;
	int* aTerrainIndices;
	TextureResource* texture;
};
#endif