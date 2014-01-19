#ifndef _DIRECTXRENDERER_H_
#define _DIRECTXRENDERER_H_

#include "Renderer.h"
#include <mmsystem.h>
#include <d3dx9.h>
#include <strsafe.h>
#include <string>
#include <map>
#include "Terrain.h"
#include "KeyboardListener.h"
#include "DirectXWindow.h"

class DirectXRenderer : public Renderer
{
public:
	LPDIRECT3D9         g_pD3D;
	LPDIRECT3DDEVICE9   g_pd3dDevice;

	DirectXRenderer();
	~DirectXRenderer();
	void Initialize(int width, int height);
	void Render(HWND hwnd, Scene* scene);
	void setRenderSize(int width, int height);
	void initTerrain(Terrain *terrain);
	void initSkybox(Skybox* skybox);

private:
	HRESULT InitD3D(HWND hWnd, int width, int height);
	void Cleanup();
	HRESULT InitGeometry(std::string filename);
	D3DPRESENT_PARAMETERS setMyRenderSize(int width, int height, bool activate);
	
	LPDIRECT3DVERTEXBUFFER9 g_pTerrainVertexBuffer = NULL; // Buffer to hold vertices
	LPDIRECT3DINDEXBUFFER9 g_pTerrainIndexBuffer = NULL;
	LPDIRECT3DTEXTURE9 terrainTexture = NULL;

	std::map <Terrain*, LPDIRECT3DVERTEXBUFFER9*> terrainVertexBuffers;
	std::map <Terrain*, LPDIRECT3DINDEXBUFFER9*> terrainIndexBuffers;

	LPDIRECT3DVERTEXBUFFER9 g_pSkyboxVertexBuffer = NULL; // Buffer to hold vertices
	LPDIRECT3DINDEXBUFFER9 g_pSkyboxIndexBuffer = NULL;
	LPDIRECT3DTEXTURE9 skyboxTexture = NULL;

	std::map <Skybox*, LPDIRECT3DTEXTURE9*> skyboxTextures;
	std::map <Skybox*, LPDIRECT3DVERTEXBUFFER9*> skyboxVertexBuffers;
	std::map <Skybox*, LPDIRECT3DINDEXBUFFER9*> skyboxIndexBuffers;


};

#endif
