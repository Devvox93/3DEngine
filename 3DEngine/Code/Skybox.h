#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include "TextureResource.h"
#include "ResourceManager.h"

struct SVertex
{
	float x,
	y,
	z,
	u,//texture coordinate x
	v;//texture coordinate y
};

class Skybox
{
public:
	Skybox(char *texturePath, ResourceManager *resourceManager);
	~Skybox();
	SVertex* aSkyboxVertices;
	int* aSkyboxIndices;
	TextureResource *texture;
private:
};

#endif