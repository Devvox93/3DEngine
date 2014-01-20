#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "Scene.h"
#include <vector>
#include "ResourceManager.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void createScene(ResourceManager* rsm, char* path);
	void deleteScene();
	Scene* getScene();
private:
	std::vector<Scene*> scenes;
	LPDIRECT3DDEVICE9 g_pd3dDevice;
};
#endif