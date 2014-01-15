#include "XResource.h"
#include <Windows.h>
#include <iostream>
#include "Logger.h"
#include <sstream>
#include <string>

XResource::XResource(char *path)

{
	g_pd3dDevice = NULL;
	g_pMesh = NULL; // Our mesh object in sysmem
	g_dwNumMaterials = 0L;   // Number of mesh materials
	LPD3DXBUFFER pD3DXMtrlBuffer;

	std::stringstream sstm;
	sstm << path;
	//std::string stemp = std::string(path);
	LPCSTR sw = sstm.str().c_str();
	//Logger::getInstance().log(WARNING, sstm.str());

	// Load the mesh from the specified file
	if (FAILED(D3DXLoadMeshFromX(sw, D3DXMESH_SYSTEMMEM,
		g_pd3dDevice, NULL,
		&pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
		&g_pMesh)))
	{
		// If model is not in current folder, try parent folder
		if (FAILED(D3DXLoadMeshFromX(sw, D3DXMESH_SYSTEMMEM,
			g_pd3dDevice, NULL,
			&pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
			&g_pMesh)))
		{
			
		}
		if (g_pd3dDevice == NULL)	//Give a visual warning if the loading of the image failed
		{
			Logger::getInstance().log(WARNING, "Could not load X from path: " + std::string(path));
			return;		//Jump out of the function
		}
	}
}
XResource::XResource()
{
}

XResource::~XResource()
{
}
