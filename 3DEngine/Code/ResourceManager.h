#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_
#include <Windows.h>
#include <d3d9.h>
#include "Resource.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	Resource* getResource(char *path);
	void PrintMap();
	LPDIRECT3DDEVICE9* g_pd3dDevice;
};
#endif