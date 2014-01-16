#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include "TextureResource.h"
#include "ResourceManager.h"
#include "Defines.h"

class Skybox
{
public:
	Skybox(char *texturePath, ResourceManager *resourceManager);
	~Skybox();
	Vertex* aSkyboxVertices;
	int* aSkyboxIndices;
	TextureResource *texture;
private:
};

#endif