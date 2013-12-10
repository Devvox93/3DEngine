#include <Windows.h>
#include "DirectXWindow.h"

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
	void newWindow();
	void updateWindows();
	bool hasActiveWindow();
private:
	WindowList* windows;
};

