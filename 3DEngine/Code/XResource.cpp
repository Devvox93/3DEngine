#include "XResource.h"
#include <Windows.h>
#include <iostream>
#include "Logger.h"
#include <sstream>
#include <string>

XResource::XResource(char *path, LPDIRECT3DDEVICE9* g_pd3dDevice, ResourceManager* rsm)
{
	std::string bla = std::string(path);

	Logger::getInstance().log(INFO, "Hoi@ " + bla);
	std::string::size_type loc = bla.find_last_of(".", 0);
	if (loc != std::string::npos) {
		//cout << "Found Omega at " << loc << endl;
		std::ostringstream oss;
		oss << "Found it at: " << loc;
		Logger::getInstance().log(INFO, oss.str());
	}
	else {
		//cout << "Didn't find Omega" << endl;
		std::ostringstream oss;
		oss << "Not found it at: " << loc;
		Logger::getInstance().log(INFO, oss.str());
	}

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

	// We need to extract the material properties and texture names from the 
	// pD3DXMtrlBuffer
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	g_pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];
	if (g_pMeshMaterials == NULL)
	{
		return;
	}
	myTextures = new TextureResource*[g_dwNumMaterials];
	for (DWORD i = 0; i < g_dwNumMaterials; i++)
	{
		// Copy the material
		g_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

		// Set the ambient color for the material (D3DX does not do this)
		g_pMeshMaterials[i].Ambient = g_pMeshMaterials[i].Diffuse;

		if (d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
		{
			// Create the texture
			myTextures[i] = rsm->getTexture(d3dxMaterials[i].pTextureFilename);
		}
	}

	// Done with the material buffer
	pD3DXMtrlBuffer->Release();

	isLoaded = true;
}

XResource::XResource()
{
}

XResource::~XResource()
{
}
