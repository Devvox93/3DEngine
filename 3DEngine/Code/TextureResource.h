#ifndef _TEXTURERESOURCE_H_
#define _TEXTURERESOURCE_H_

#include "Resource.h"
#include <d3dx9.h>
#include <string>
class TextureResource : public Resource
{
public:
	TextureResource(std::string path, LPDIRECT3DDEVICE9* g_pd3dDevice);
	TextureResource();
	~TextureResource();
	LPDIRECT3DTEXTURE9 texture;
};

#endif