/*
	3D Engine
	Skybox.h
	Purpose: Holds information about the skybox.

	@author Patrick, Nick, Robert, Jordi
	@version 1.0
*/

#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include "TextureResource.h"
#include "ResourceManager.h"
#include "Defines.h"

class Skybox
{
public:
	/*
		Loads a texture for the skybox and applies it.

		@param textureResource: A pointer to the texture resource of the Skybox.
		@param *resourceManager: A pointer to the resourceManager.
	*/
	Skybox(TextureResource* textureResource, ResourceManager *resourceManager);
	~Skybox();

	/*
		Returns a pointer.

		@return Vertex*: A pointer to the vertices of Skybox.
	*/
	Vertex* getVertices();

	/*
		Returns a pointer.

		@return int*: A pointet to the indices of Skybox.
	*/
	int* getIndices();

	/*
		Returns a pointer.

		@return TextureResource*: The resource of the Skybox.
	*/
	TextureResource* getTextureResource();
private:
	Vertex* aSkyboxVertices;
	int* aSkyboxIndices;
	TextureResource* texture;
};
#endif