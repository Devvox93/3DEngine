#include "SceneManager.h"


SceneManager::SceneManager()
{
	scenes = std::vector<Scene*>();
};


SceneManager::~SceneManager()
{
};

void SceneManager::createScene()
{
	Scene *newScene = new Scene();

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
	Scene *scene = new Scene();
	return scene;
};