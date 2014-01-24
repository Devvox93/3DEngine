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
<<<<<<< HEAD
=======
	~DirectXWindow();
>>>>>>> b5be66274fd88ea8db96b62012391e3c9f26537f

	/*
		 Creates and sets variables of a new window, specifically for Direct X.

		 @param *directXRenderer: A pointer to the DirectX renderer.
	*/
<<<<<<< HEAD
=======
	~DirectXWindow();
>>>>>>> 04ac3ee... Destructors (patrick houdt van mannen.)
=======
>>>>>>> b5be66274fd88ea8db96b62012391e3c9f26537f
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