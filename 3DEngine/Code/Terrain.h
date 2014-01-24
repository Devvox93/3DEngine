/*
<<<<<<< HEAD
	3D Engine
=======
3D Engine
>>>>>>> b5be66274fd88ea8db96b62012391e3c9f26537f
	Terrain.h
	Purpose: Holds information about the terrain.

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
	/*
<<<<<<< HEAD
		Loads a heightmap and texture for the terrain.

		@param path: The path to the heightmap file on disk.
		@param texturepath: The path to the texture file on disk.
		@param *resourceManager: A pointer to the resourcemanager to load the resources from disk.
	*/
	Terrain(std::string path, std::string texturepath, ResourceManager *resourceManager);
=======
	Loads a heightmap and texture for the terrain.

	@param path: The path to the heightmap file on disk.
	@param textureResource: A pointer to the texture resource.
	@param *resourceManager: A pointer to the resourcemanager to load the resources from disk.
	*/
	Terrain(std::string path, TextureResource* textureResource, ResourceManager *resourceManager);
>>>>>>> b5be66274fd88ea8db96b62012391e3c9f26537f
	~Terrain();

	/*
		Returns a variable.

		@return int: The width of the terrain.
	*/
	int getWidth();

	/*
		Returns a variable.

		@return int: The height of the terrain.
	*/
	int getHeight();

	/*
		Returns a variable.

		@return Vertex*: A pointer to the vertices of the terrain.
	*/
	Vertex* getVertices();

	/*
		Returns a variable.

		@return int: The amount of indices in the terrain.
	*/
	int getAmountOfIndices();

	/*
		Returns a variable.

		@return int*: A pointer to the indices in the terrain.
	*/
	int* getIndices();

	/*
		Returns a variable.

		@return TextureResource*: The texture of the terrain.
	*/
	TextureResource* getTextureResource();
private:
	TerrainData* data;
	Vertex* aTerrainVertices;
	int amountOfIndices;
	int* aTerrainIndices;
	TextureResource* texture;
};
#endif