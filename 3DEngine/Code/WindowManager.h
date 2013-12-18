#ifndef _WINDOWMANAGER_H_
#define _WINDOWMANAGER_H_


#include <Windows.h>
#include "DirectXWindow.h"
#include "Renderer.h"

struct WindowList
{
	DirectXWindow* window;
	WindowList* next;
};


class WindowManager
{
public:
	WindowManager();
	~WindowManager();
	void newWindow(Renderer *renderer);
	void updateWindows();
	bool hasActiveWindow();
	DirectXWindow* getLastWindow();
private:
	WindowList* windows;
};

#endif
