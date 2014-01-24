/*
	3D Engine
	DirectXRenderer.h
	Purpose: DirectX

	@author Patrick, Nick, Robert, Jordi
	@version 1.0
*/

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

	/*
		 Abstract method that initializes the renderer.

		@param width: The width of the window that will be created.
		@param height: The height of the window that will be created.
	*/
	void Initialize(int width, int height);

	/*
		 Abstract method that renders.

		@param hwnd: The hwnd of the window where the render output needs to be put.
		@param scene: A pointer to the scene that needs to be rendered.
	*/
	void Render(HWND hwnd, Scene* scene);

	/*
		 Abstract method that sets the render size.

		@param width: The width of the window that will be created.
		@param height: The height of the window that will be created.
	*/
	void setRenderSize(int width, int height);

	/*
		 Abstract method that initializes the skybox.

		@param *skybox: Pointer to the skybox that needs to be initialized.
	*/
	void initSkybox(Skybox* skybox);

	/*
		 Abstract method that initializes the terrain.

		@param *terrain: A pointer to the terrain that needs to be initialized.
	*/
	void initTerrain(Terrain *terrain);
	LPDIRECT3DDEVICE9 getD3DDevice();
private:
	LPDIRECT3D9         g_pD3D;
	LPDIRECT3DDEVICE9   g_pd3dDevice;
	HRESULT InitD3D(HWND hWnd, int width, int height);
	HRESULT InitGeometry(std::string filename);
	D3DPRESENT_PARAMETERS setMyRenderSize(int width, int height, bool activate);

	std::map <Terrain*, LPDIRECT3DVERTEXBUFFER9> terrainVertexBuffers;
	std::map <Terrain*, LPDIRECT3DINDEXBUFFER9> terrainIndexBuffers;

	std::map <Skybox*, LPDIRECT3DVERTEXBUFFER9> skyboxVertexBuffers;
	std::map <Skybox*, LPDIRECT3DINDEXBUFFER9> skyboxIndexBuffers;
};
#endif
