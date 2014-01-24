/*
	3D Engine
	DirectXWindow.h
	Purpose: Window with specific functions for DirectX.

	@author Patrick, Nick, Robert, Jordi
	@version 1.0
*/

#ifndef _DIRECTXWINDOW_H_
#define _DIRECTXWINDOW_H_

#include "Window.h"
#include "DirectXRenderer.h"

class DirectXWindow : public Window
{
public:
	DirectXWindow();
<<<<<<< HEAD

	/*
		 Creates and sets variables of a new window, specifically for Direct X.

		 @param *directXRenderer: A pointer to the DirectX renderer.
	*/
=======
	~DirectXWindow();
>>>>>>> 04ac3ee... Destructors (patrick houdt van mannen.)
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