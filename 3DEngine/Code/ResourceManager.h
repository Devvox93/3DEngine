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
	Resource* getResource(std::string path);
	TextureResource* getTexture(std::string path);
	void PrintMap();
	std::vector<std::string>* getSceneFile(std::string path);
	void setD3DDevice(LPDIRECT3DDEVICE9 device);
private:
	std::map<std::string, Resource*> ResourceMap;
	LPDIRECT3DDEVICE9 g_pd3dDevice;
};
#endif