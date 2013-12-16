#include <windows.h>
#include "Window.h"
#include "Logger.h"

Window::Window()
{
	//Set the default data for the window class.
	//These can be reset in the derived class's constructor.

	_WndClass.cbSize = sizeof(_WndClass);
	_WndClass.style = CS_DBLCLKS;
	_WndClass.lpfnWndProc = BaseWndProc;
	_WndClass.cbClsExtra = 0;
	_WndClass.cbWndExtra = 0;
	_WndClass.hInstance = NULL;
	_WndClass.hIcon = NULL;
	_WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	_WndClass.hbrBackground =
		(HBRUSH)GetStockObject(WHITE_BRUSH);
	_WndClass.lpszMenuName = NULL;
	_WndClass.hIconSm = NULL;

	_dwExtendedStyle = NULL;
	_dwStyle = NULL;
	_pszClassName = "Window";
	_pszTitle = "";
}

HWND Window::Create(int x, int y, int nWidth, int nHeight,
	HWND hParent, HMENU hMenu, HINSTANCE hInstance)
{
	_WndClass.lpszClassName = _pszClassName;
	_WndClass.hInstance = hInstance;

	//If we're already registered, this call will fail.
	RegisterClassEx(&_WndClass);

	_hwnd = CreateWindowEx(_dwExtendedStyle, _pszClassName,
		_pszTitle, _dwStyle, x, y, nWidth, nHeight,
		hParent, hMenu, hInstance, (void*)this);
	state = normal;
	return _hwnd;
}

LRESULT CALLBACK Window::BaseWndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	//A pointer to the object is passed in the CREATESTRUCT
	if (msg == WM_NCCREATE)
	{
		SetWindowLongPtr(hwnd, GWLP_USERDATA,
			(LONG_PTR)((LPCREATESTRUCT)lParam)->lpCreateParams);
	}
	
	//Retrieve the pointer
	Window *pObj =
		(Window *)GetWindowLongPtr(hwnd, GWLP_USERDATA);

	//Filter message through child classes
	if (pObj)
	{
		return pObj->WindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;//hier komen wij niet vaak, één keer per scherm als het goed is...
}

LRESULT Window::WindowProc(HWND hwnd, UINT msg, WPARAM wParam,
	LPARAM lParam)
{
	//This may be overridden to process messages.
	switch (msg)
	{
	case WM_PAINT:
		render();
		break;
	default:
		return NULL;
	}
	return NULL;
}

void Window::render()
{
	RECT rect;
	HDC hDC = GetDC(_hwnd);
	PAINTSTRUCT PaintStruct;
	BeginPaint(_hwnd, &PaintStruct);
	GetClientRect(_hwnd, &rect);
	DrawText(hDC, "Hallo, scherm dat verdomd moeilijk te krijgen is!", 49, &rect,
		DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	EndPaint(_hwnd, &PaintStruct);
	ReleaseDC(_hwnd, hDC);
}