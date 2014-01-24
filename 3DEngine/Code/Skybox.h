#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include "TextureResource.h"
#include "ResourceManager.h"
#include "Defines.h"

class Skybox
{
public:
	Skybox(TextureResource* textureResource, ResourceManager *resourceManager);
	~Skybox();
	Vertex* getVertices();
	int* getIndices();
	TextureResource* getTextureResource();
private:
	Vertex* aSkyboxVertices;
	int* aSkyboxIndices;
	TextureResource* texture;
};
#endif