#include "Scene.h"
#include "Model.h"
#include "Camera.h"
#include "Logger.h"

Scene::Scene(ResourceManager* resourceManager)
{
	entities = std::vector<Entity*>();
	terrain = new Terrain("clouds.bmp", "tex.bmp", resourceManager); // Terrain has to be loaded
	skybox = new Skybox("skybox.jpg", resourceManager);
	createEntity(MODEL, resourceManager);
}


Scene::~Scene()
{
}

void Scene::createEntity(Entities sort, ResourceManager* rsm){
	Entity *newEntity;

	switch (sort)
	{
	case(CAMERA) :
		newEntity = new Camera();
		break;
	case(MODEL) :
		newEntity = new Model();
		((Model*)newEntity)->model = (XResource*)rsm->getResource("car.X");
		break;
	default:
		Logger::getInstance().log(WARNING, "Entity fout");
		break;
	}

	entities.push_back(newEntity);
};

void Scene::deleteEntity(Entity* entity){
	// destroy and delete passed entity from lijst
};

void Scene::render()
{
	//???
};

void Scene::loadEntities()
{
	//???
};

void Scene::updateEntities()
{

};

std::vector<Entity*> Scene::getEntities(){
	return entities;
};

Terrain* Scene::getTerrain()
{
	return terrain;
};

Skybox* Scene::getSkybox()
{
	return skybox;
};
