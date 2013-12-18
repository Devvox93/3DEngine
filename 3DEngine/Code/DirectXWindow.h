#ifndef _DIRECTXWINDOW_H_
#define _DIRECTXWINDOW_H_

#include "Window.h"
#include "Renderer.h"

class DirectXWindow : public Window
{
public:
	DirectXWindow(Renderer *directXRenderer);
	virtual void render();
protected:
	Renderer *renderer;

	virtual LRESULT WindowProc(HWND hwnd, UINT msg,
		WPARAM wParam, LPARAM lParam);

	virtual void OnDestroy(HWND hwnd);
};

#endif