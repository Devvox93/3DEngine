#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <strsafe.h>
#include <string>



class Renderer
{
public:
	LPDIRECT3D9         g_pD3D;
	LPDIRECT3DDEVICE9   g_pd3dDevice;

	LPD3DXMESH          g_pMesh; // Our mesh object in sysmem
	D3DMATERIAL9*       g_pMeshMaterials; // Materials for our mesh
	LPDIRECT3DTEXTURE9* g_pMeshTextures; // Textures for our mesh
	DWORD               g_dwNumMaterials;   // Number of mesh materials

	Renderer();
	~Renderer();
	VOID Initialize(HWND hWnd);
	VOID Render(HWND hwnd);

private:
	HRESULT InitD3D(HWND hWnd);
	VOID Cleanup();
	VOID SetupMatrices();
	HRESULT InitGeometry(std::string filename);
	void WorldMatrix(bool right);
};

#endif