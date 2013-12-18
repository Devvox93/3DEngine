#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <Windows.h>

class Renderer
{
public:
	Renderer();
	~Renderer();
	virtual void Initialize(HWND hWnd) = 0;
	virtual void Render(HWND hwnd) = 0;
	virtual bool alreadyInitialized() = 0;
private:

};

#endif // !_RENDERER_H_
