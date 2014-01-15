#include "Resource.h"
#include <d3dx9.h>

class XResource : public Resource
{
public:
	LPD3DXMESH          g_pMesh; // Our mesh object in sysmem
	D3DMATERIAL9*       g_pMeshMaterials; // Materials for our mesh
	LPDIRECT3DTEXTURE9* g_pMeshTextures; // Textures for our mesh
	DWORD               g_dwNumMaterials;   // Number of mesh materials
	XResource(char *path, LPDIRECT3DDEVICE9* g_pd3dDevice);
	XResource();
	~XResource();
};

