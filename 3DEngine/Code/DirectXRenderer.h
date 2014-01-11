#ifndef _DIRECTXRENDERER_H_
#define _DIRECTXRENDERER_H_

#include "Renderer.h"
#include <mmsystem.h>
#include <d3dx9.h>
#include <strsafe.h>
#include <string>
#include "Terrain.h"
#include "KeyboardListener.h"
#include "DirectXWindow.h"

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
	void Initialize(int width, int height);
	void Render(HWND hwnd, Scene scene);
	void setActiveCamera(Camera* camera);
	void setRenderSize(int width, int height);

private:
	HRESULT InitD3D(HWND hWnd, int width, int height);
	void Cleanup();
	HRESULT InitGeometry(std::string filename);
	void WorldMatrix(int type);
	void initHeightmap();

	LPDIRECT3DVERTEXBUFFER9 g_pHeightmapVertexBuffer = NULL; // Buffer to hold vertices
	LPDIRECT3DINDEXBUFFER9 g_pHeightmapIndexBuffer = NULL;
	Terrain *terrain;
	LPDIRECT3DTEXTURE9 terrainTexture;

	Camera* activeCamera;
};

#endif
