#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <strsafe.h>

class Renderer
{
public:
	Renderer();
	~Renderer();
	HRESULT InitD3D(HWND hWnd);
	VOID Cleanup();
	VOID SetupMatrices();
	LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

