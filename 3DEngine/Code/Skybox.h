/*
3D Engine
Xresource.h
Purpose: Loads X resources.

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
	Skybox(std::string texturePath, ResourceManager *resourceManager);
	~Skybox();
	Vertex* getVertices();
	int* getIndices();
	TextureResource* getTextureResource();
private:
	Vertex* aSkyboxVertices;
	int* aSkyboxIndices;
	TextureResource *texture;
};
#endif