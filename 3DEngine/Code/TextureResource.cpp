#include "TextureResource.h"
#include "Logger.h"

TextureResource::TextureResource(std::string path, LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice, path.c_str(), &texture)))
	{
		std::string lol = std::string(path);
		Logger::getInstance().log(WARNING, "Could not find texture: " + lol);
		isLoaded = false;
		return;
	}
	isLoaded = true;
};

TextureResource::TextureResource()
{
	isLoaded = false;
}

TextureResource::~TextureResource()
{
	if (texture != NULL){
		delete texture;
		texture = NULL;
	}
};

LPDIRECT3DTEXTURE9 TextureResource::getTexture()
{
	return texture;
}