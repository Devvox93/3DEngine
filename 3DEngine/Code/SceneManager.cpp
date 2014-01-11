#include "SceneManager.h"


SceneManager::SceneManager()
{
	scenes = std::vector<Scene>();
}


SceneManager::~SceneManager()
{
}

void SceneManager::createScene(){
	Scene *newScene = new Scene;

	scenes.push_back(*newScene);
};

void SceneManager::deleteScene(){

};

Scene SceneManager::returnScene()
{

};