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
	DirectXRenderer();
	~DirectXRenderer();
	void Initialize(int width, int height);
	void Render(HWND hwnd, Scene* scene);
	void setRenderSize(int width, int height);
	void initTerrain(Terrain *terrain);
	void initSkybox(Skybox* skybox);
	LPDIRECT3DDEVICE9 getD3DDevice();
private:
	LPDIRECT3D9         g_pD3D;
	LPDIRECT3DDEVICE9   g_pd3dDevice;
	HRESULT InitD3D(HWND hWnd, int width, int height);
	void Cleanup();
	HRESULT InitGeometry(std::string filename);
	D3DPRESENT_PARAMETERS setMyRenderSize(int width, int height, bool activate);

	std::map <Terrain*, LPDIRECT3DVERTEXBUFFER9> terrainVertexBuffers;
	std::map <Terrain*, LPDIRECT3DINDEXBUFFER9> terrainIndexBuffers;

	std::map <Skybox*, LPDIRECT3DVERTEXBUFFER9> skyboxVertexBuffers;
	std::map <Skybox*, LPDIRECT3DINDEXBUFFER9> skyboxIndexBuffers;
};
#endif
