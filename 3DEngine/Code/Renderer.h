#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <strsafe.h>



class Renderer
{
public:
	LPDIRECT3D9         g_pD3D;
	LPDIRECT3DDEVICE9   g_pd3dDevice;

	Renderer();
	~Renderer();
	VOID Initialize(HWND hWnd);
	VOID Render(HWND hwnd);

private:
	HRESULT InitD3D(HWND hWnd);
	VOID Cleanup();
	VOID SetupMatrices();
};

#endif