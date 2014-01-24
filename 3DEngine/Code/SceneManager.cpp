#include "SceneManager.h"


SceneManager::SceneManager()
{
	scenes = std::map<HWND, Scene*>();
};


SceneManager::~SceneManager()
{
};

void SceneManager::createScene(ResourceManager* resourceManager, std::string path, HWND hwnd, Renderer* renderer)
{
	Scene* newScene = new Scene(path, resourceManager);

	scenes[hwnd] = newScene;
	if (newScene->getTerrain())
	{
		renderer->initTerrain(newScene->getTerrain());
	}
	if (newScene->getSkybox())
	{
		renderer->initSkybox(newScene->getSkybox());
	}
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