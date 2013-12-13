#include "Window.h"
#include "Renderer.h"

class DirectXWindow : public Window
{
public:
	DirectXWindow(Renderer *directXRenderer);
protected:
	Renderer *renderer;

	virtual LRESULT WindowProc(HWND hwnd, UINT msg,
		WPARAM wParam, LPARAM lParam);

	virtual void OnDestroy(HWND hwnd);
	virtual void OnPaint(HWND hwnd);
};