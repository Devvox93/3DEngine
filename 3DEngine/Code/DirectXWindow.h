#ifndef _DIRECTXWINDOW_H_
#define _DIRECTXWINDOW_H_

#include "Window.h"
#include "DirectXRenderer.h"

class DirectXWindow : public Window
{
public:
	DirectXWindow();
	DirectXWindow(Renderer *directXRenderer);
	virtual void render(Scene *scene);
protected:
	Renderer *renderer;
	virtual LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual void OnDestroy(HWND hwnd);
private:
	void resize();
};
#endif