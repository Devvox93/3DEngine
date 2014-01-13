#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_
#include "Scene.h"
#include <vector>

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void createScene();
	void deleteScene();
	Scene returnScene();
private:
	std::vector<Scene> scenes;
};
#endif