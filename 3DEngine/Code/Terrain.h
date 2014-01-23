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
	Terrain(std::string path, std::string texturepath, ResourceManager *resourceManager);
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