#ifndef _DIRECTXRENDERER_H_
#define _DIRECTXRENDERER_H_

#include "Renderer.h"
#include <mmsystem.h>
#include <d3dx9.h>
#include <strsafe.h>
#include <string>


class DirectXRenderer : public Renderer
{
public:
	LPDIRECT3D9         g_pD3D;
	LPDIRECT3DDEVICE9   g_pd3dDevice;

	LPD3DXMESH          g_pMesh; // Our mesh object in sysmem
	D3DMATERIAL9*       g_pMeshMaterials; // Materials for our mesh
	LPDIRECT3DTEXTURE9* g_pMeshTextures; // Textures for our mesh
	DWORD               g_dwNumMaterials;   // Number of mesh materials

	DirectXRenderer();
	~DirectXRenderer();
	void Initialize(HWND hWnd);
	void Render(HWND hwnd);

private:
	HRESULT InitD3D(HWND hWnd);
	void Cleanup();
	void SetupMatrices();
	HRESULT InitGeometry(std::string filename);
	void WorldMatrix(bool right);
};

#endif
