/*
	3D Engine
	SceneManager.h
	Purpose: Manages scenes.

	@author Patrick, Nick, Robert, Jordi
	@version 1.0
*/

#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "Scene.h"
#include "ResourceManager.h"
#include "Windows.h"
#include "Renderer.h"
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	/*
		Creates a scene.

		@param rsm: A pointer to the Resourcemanager to load scene information from file.
		@param path: Path to the scenefile on disk.
		@param hwnd: The hwnd in which the scene will be rendered.
		@param renderer: A pointer to the renderer.
	*/
	void createScene(ResourceManager* rsm, std::string path, HWND hwnd, Renderer* renderer);
	void deleteScene();

	/*
		Returns a pointer to a scene in a hwnd.

		@return Scene*: A pointer to the scene.
		@param hwnd: The hwnd of which the scene must be returned.
	*/
	Scene* getScene(HWND hwnd);
private:
	std::map<HWND, Scene*> scenes;
};
#endif