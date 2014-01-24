/*
3D Engine
Xresource.h
Purpose: Loads X resources.

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

	void createScene(ResourceManager* rsm, std::string path, HWND hwnd, Renderer* renderer);
	void deleteScene();
	Scene* getScene(HWND hwnd);
private:
	std::map<HWND, Scene*> scenes;
};
#endif