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
	Resource* getResource(char *path);
	TextureResource* getTexture(char *path);
	void PrintMap();
	LPDIRECT3DDEVICE9* g_pd3dDevice;
	std::vector<std::string>* getSceneFile(char* path);
private:
	std::map<std::string, Resource*> ResourceMap;
};
#endif