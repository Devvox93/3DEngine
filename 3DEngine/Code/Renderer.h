#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <Windows.h>
#include "Camera.h"

class Renderer
{
public:
	Renderer();
	~Renderer();
	virtual void Initialize(HWND hWnd, int width, int height) = 0;
	virtual void Render(HWND hwnd) = 0;
	virtual void setActiveCamera(Camera* camera) = 0;
	virtual void setRenderSize(int width, int height) = 0;
private:
	Camera* activeCamera;
};

#endif // !_RENDERER_H_
