#include <Windows.h>
enum WindowState { fullscreen, maximized, normal, minimized, closed };
class Window
{
public:
	Window();
	HWND Create(int x, int y, int nWidth, int nHeight,
		HWND hParent, HMENU hMenu, HINSTANCE hInstance);
	HWND _hwnd;
	WindowState state;

protected:
	static LRESULT CALLBACK BaseWndProc(HWND hwnd, UINT msg,
		WPARAM wParam, LPARAM lParam);

	virtual LRESULT WindowProc(HWND hwnd, UINT msg,
		WPARAM wParam, LPARAM lParam);

	WNDCLASSEX _WndClass;
	DWORD _dwExtendedStyle;
	DWORD _dwStyle;
	LPSTR _pszClassName;
	LPSTR _pszTitle;
};