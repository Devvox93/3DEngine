#include "Window.h"

class DirectXWindow : public Window
{
public:
	DirectXWindow();
protected:
	virtual LRESULT WindowProc(HWND hwnd, UINT msg,
		WPARAM wParam, LPARAM lParam);

	virtual void OnDestroy(HWND hwnd);
	virtual void OnPaint(HWND hwnd);
};