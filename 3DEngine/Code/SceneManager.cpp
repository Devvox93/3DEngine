#include "SceneManager.h"


SceneManager::SceneManager()
{
	scenes = std::vector<Scene*>();
};


SceneManager::~SceneManager()
{
};

void SceneManager::createScene(ResourceManager* resourceManager, char* path)
{
	Scene* newScene = new Scene(path, resourceManager);

	scenes.push_back(newScene);
};

void SceneManager::deleteScene()
{

};

Scene* SceneManager::getScene()
{
	for each (Scene* current in scenes)
	{
		return current;
	}
	//Scene *scene = scenes.front();
	return NULL;
};