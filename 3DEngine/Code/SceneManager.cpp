#include "SceneManager.h"


SceneManager::SceneManager()
{
	scenes = std::vector<Scene>();
}


SceneManager::~SceneManager()
{
}

void createScene(){
	Scene *newScene = new Scene;

	scenes.push_back(newScene);
};

void deleteScene(){

};