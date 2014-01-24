#include "SceneManager.h"


SceneManager::SceneManager()
{
	scenes = std::map<HWND, Scene*>();
};


SceneManager::~SceneManager()
{
	scenes.clear();
};

void SceneManager::createScene(ResourceManager* resourceManager, std::string path, HWND hwnd, Renderer* renderer)
{
	Scene* newScene = new Scene(path, resourceManager);

	scenes[hwnd] = newScene;
	
	renderer->initTerrain(newScene->getTerrain());
	renderer->initSkybox(newScene->getSkybox());
};

void SceneManager::deleteScene()
{

};

Scene* SceneManager::getScene(HWND hwnd)
{
	if (scenes.count(hwnd))
	{
		return scenes[hwnd];
	}
	return NULL;
};