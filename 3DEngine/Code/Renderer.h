/*
	3D Engine
	Renderer.h
	Purpose: Abstract class, meant as interface to specific render engines.

	@author Patrick, Nick, Robert, Jordi
	@version 1.0
*/

#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <Windows.h>
#include "Camera.h"
#include "Scene.h"
#include "Skybox.h"

class Renderer
{
public:
	Renderer();
	virtual ~Renderer() = 0;

	/*
		 Abstract method that initializes the renderer.

		@param width: The width of the window that will be created.
		@param height: The height of the window that will be created.
	*/
	virtual void Initialize(int width, int height) = 0;

	/*
		 Abstract method that renders.

		@param hwnd: The hwnd of the window where the render output needs to be put.
		@param scene: A pointer to the scene that needs to be rendered.
	*/
	virtual void Render(HWND hwnd, Scene* scene) = 0;

	/*
		 Abstract method that sets the render size.

		@param width: The width of the window that will be created.
		@param height: The height of the window that will be created.
	*/
	virtual void setRenderSize(int width, int height) = 0;

	/*
		 Abstract method that initializes the skybox.

		@param *skybox: Pointer to the skybox that needs to be initialized.
	*/
	virtual void initSkybox(Skybox *skybox) = 0;

	/*
		 Abstract method that initializes the terrain.

		@param *terrain: A pointer to the terrain that needs to be initialized.
	*/
	virtual void initTerrain(Terrain *terrain) = 0;
private:
};
#endif