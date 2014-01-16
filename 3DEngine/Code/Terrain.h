#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include "TextureResource.h"
#include "ResourceManager.h"

typedef unsigned char BYTE;

struct TerrainData
{
	int width;
	int height;
};

struct Vertex
{
	float x,
	y,
	z,
	u,//texture coordinate x
	v;//texture coordinate y
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