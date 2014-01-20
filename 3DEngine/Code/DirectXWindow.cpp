#include <windows.h>
#include "DirectXWindow.h"
#include "Logger.h"
#include <sstream>

DirectXWindow::DirectXWindow()
{
};

DirectXWindow::DirectXWindow(Renderer *directXRenderer)
{
	//Override class name and style attributes.
	_pszClassName = "DirectXWindow";
	_pszTitle = "Stop met het lezen van deze titel, het kost meer tijd dan het waard is.";
	_dwStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	_WndClass.style |= CS_HREDRAW | CS_VREDRAW;

	renderer = directXRenderer;
	resize();
};

LRESULT DirectXWindow::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
	case WM_SIZE:
		resize();
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
};

void DirectXWindow::resize()
{
	RECT rect;
	if (GetWindowRect(_hwnd, &rect))
	{
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		renderer->setRenderSize(width, height);
	}
};

void DirectXWindow::OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
};

void DirectXWindow::render(Scene *scene)
{
	if (scene)
	{
		scene->updateEntities();
	}
	renderer->Render(_hwnd, scene);
};