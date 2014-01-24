/*
3D Engine
Xresource.h
Purpose: Loads X resources.

@author Patrick, Nick, Robert, Jordi
@version 1.0
*/

#ifndef _WINDOWMANAGER_H_
#define _WINDOWMANAGER_H_

#include <Windows.h>
#include "Window.h"
#include "DirectXWindow.h"
#include "Renderer.h"

struct WindowList
{
	Window* window;
	WindowList* next;
};

class WindowManager
{
public:
	WindowManager(SceneManager *sceneManager);
	~WindowManager();
	void newWindow(Renderer *renderer, int x, int y, int width, int height);
	void updateWindows();
	bool hasActiveWindow();
	Window* getLastWindow();
private:
	WindowList *list;
	WindowList* windows;
	SceneManager *sceneManager;
};
#endif
