#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include "TextureResource.h"
#include "ResourceManager.h"
#include "Defines.h"

typedef unsigned char BYTE;

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
	TerrainData* data;
	Vertex* aTerrainVertices;
	int amountOfIndices;
	int* aTerrainIndices;
	TextureResource *texture;
private:
};

#endif