#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <Windows.h>
#include "SceneManager.h"
#include "Scene.h"
enum WindowState { fullscreen, maximized, normal, minimized, closed };
class Window
{
public:
	Window();
	HWND Create(int x, int y, int nWidth, int nHeight,
		HWND hParent, HMENU hMenu, HINSTANCE hInstance);
	HWND _hwnd;
	WindowState state;
	virtual void render(Scene *scene);

protected:
	static LRESULT CALLBACK BaseWndProc(HWND hwnd, UINT msg,
		WPARAM wParam, LPARAM lParam);

	virtual LRESULT WindowProc(HWND hwnd, UINT msg,
		WPARAM wParam, LPARAM lParam);

	WNDCLASSEX _WndClass;
	DWORD _dwExtendedStyle;
	DWORD _dwStyle;
	LPSTR _pszClassName;
	LPSTR _pszTitle;
};

#endif