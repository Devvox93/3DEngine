/*
	3D Engine
	ResourceManager.h
	Purpose: Manages the loading and unloading of resource files on disk.

	@author Patrick, Nick, Robert, Jordi
	@version 1.0
*/

#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include <Windows.h>
#include <d3d9.h>
#include "Resource.h"
#include "TextureResource.h"
#include <map>
#include <string>
#include <vector>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	/*
		Returns a pointer.

		@return Resource*: A pointer to a resource.
		@param path: The path to the resource file on disk which needs to be loaded.
	*/
	Resource* getResource(std::string path);

	/*
		Returns a pointer.

		@return TextureResource*: A pointer to a texture resource.
		@param path: The path to the resouce file on disk which needs to be loaded.
	*/
	TextureResource* getTexture(std::string path);

	/*
		Prints the entire map of resources.
	*/
	void PrintMap();

	/*
		Returns a pointer.

		@return vector<string>*: A vector of strings containting data from a scene file.
		@param path: The path to a scene file on disk.
	*/
	std::vector<std::string>* getSceneFile(std::string path);

	/*
		Sets the D3DDevice, which is used for loading resources.

		@param device: The device that needs to be set.
	*/
	void setD3DDevice(LPDIRECT3DDEVICE9 device);
private:
	std::map<std::string, Resource*> ResourceMap;
	Resource *bmprsrc;
	Resource *xrsrc;
	TextureResource *txrsrc;
	LPDIRECT3DDEVICE9 g_pd3dDevice;
};
#endif