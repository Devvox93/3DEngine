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
private:
	WindowList* windows;
};

