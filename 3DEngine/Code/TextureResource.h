/*!
	3D Engine
	TextureResource.h
	Purpose: Loads and stores a texture.

	@author Patrick, Nick, Robert, Jordi
	@version 1.0
*/

#ifndef _TEXTURERESOURCE_H_
#define _TEXTURERESOURCE_H_

#include "Resource.h"
#include <d3dx9.h>
#include <string>

class TextureResource : public Resource
{
public:
	/*!
		Loads a texture resource from file.

		@param path: The path to the resource file on disk.
		@param g_pd3dDevice: The Direct X devide used to load the texture.
	*/
	TextureResource(std::string path, LPDIRECT3DDEVICE9 g_pd3dDevice);
	TextureResource();
	~TextureResource();

	/*!
		Returns the texture.

		@return LPDIRECT3DTEXTURE9: The texture.
	*/
	LPDIRECT3DTEXTURE9 getTexture();
private:
	LPDIRECT3DTEXTURE9 texture;
};
#endif