#include <windows.h>
#include "DirectXWindow.h"
#include "Logger.h"
#include <sstream>



DirectXWindow::DirectXWindow(Renderer *directXRenderer)
{
	//Override class name and style attributes.
	_pszClassName = "DirectXWindow";
	_pszTitle = "YoloSwag Scherm";
	_dwStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	_WndClass.style |= CS_HREDRAW | CS_VREDRAW;

	renderer = directXRenderer;
}

LRESULT DirectXWindow::WindowProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		state = closed;
		PostQuitMessage(0);
		break;
	/*case WM_PAINT:
		render();

		break;*/
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

void DirectXWindow::OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}

void DirectXWindow::render()
{
	renderer->Render(_hwnd);
}