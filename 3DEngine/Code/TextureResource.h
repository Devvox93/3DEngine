#pragma once
#include "Resource.h"
#include <d3dx9.h>
class TextureResource : public Resource
{
public:
	TextureResource(char *path, LPDIRECT3DDEVICE9* g_pd3dDevice);
	TextureResource();
	~TextureResource();
	LPDIRECT3DTEXTURE9 texture;
};

