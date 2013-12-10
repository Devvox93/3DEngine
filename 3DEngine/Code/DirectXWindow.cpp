#include <windows.h>
#include "DirectXWindow.h"
#include "Logger.h"
#include <sstream>


DirectXWindow::DirectXWindow()
{
	//Override class name and style attributes.
	_pszClassName = "DirectXWindow";
	_pszTitle = "YoloSwag Scherm";
	_dwStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	_WndClass.style |= CS_HREDRAW | CS_VREDRAW;
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
	case WM_PAINT:
		OnPaint(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

void DirectXWindow::OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}

void DirectXWindow::OnPaint(HWND hwnd)
{
	RECT rect;
	HDC hDC = GetDC(hwnd);
	PAINTSTRUCT PaintStruct;
	BeginPaint(hwnd, &PaintStruct);
	GetClientRect(hwnd, &rect);
	DrawText(hDC, "Hallo, scherm dat verdomd moeilijk te krijgen is!", 49, &rect,
		DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	EndPaint(hwnd, &PaintStruct);
	ReleaseDC(hwnd, hDC);
}