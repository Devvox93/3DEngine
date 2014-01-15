#include "XResource.h"
#include <Windows.h>
#include <iostream>
#include "Logger.h"
#include <sstream>
#include <string>

XResource::XResource(char *path, LPDIRECT3DDEVICE9* g_pd3dDevice)
{
	g_pMesh = NULL; // Our mesh object in sysmem
	g_dwNumMaterials = 0L;   // Number of mesh materials
	LPD3DXBUFFER pD3DXMtrlBuffer;

	// Load the mesh from the specified file
	if (FAILED(D3DXLoadMeshFromX(path, D3DXMESH_SYSTEMMEM,
		*g_pd3dDevice, NULL,
		&pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
		&g_pMesh)))
	{
		Logger::getInstance().log(WARNING, "Could not load X from path: " + std::string(path));
		isLoaded = false;
		return;		//Jump out of the function
	}
	isLoaded = true;
}

XResource::XResource()
{
}

XResource::~XResource()
{
}
