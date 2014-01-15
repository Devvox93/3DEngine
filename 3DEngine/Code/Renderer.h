#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <Windows.h>
#include "Camera.h"
#include "Scene.h"

class Renderer
{
public:
	Renderer();
	~Renderer();
	virtual void Initialize(int width, int height) = 0;
	virtual void Render(HWND hwnd, Scene* scene) = 0;
	virtual void setActiveCamera(Camera* camera) = 0;
	virtual void setRenderSize(int width, int height) = 0;
	virtual void initSkybox() = 0;
	virtual void initTerrain(Terrain *terrain) = 0;
private:
	Camera* activeCamera;
};

#endif // !_RENDERER_H_
