#include "SceneManager.h"


SceneManager::SceneManager()
{
	scenes = std::vector<Scene*>();
};


SceneManager::~SceneManager()
{
};

void SceneManager::createScene(ResourceManager* rsm)
{
	Scene *newScene = new Scene(rsm);

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