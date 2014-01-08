#include "Scene.h"
#include "Model.h"
#include "Camera.h"
#include "Logger.h"

Scene::Scene()
{
	entities = std::vector<Entity*>();
	terrain = new Terrain("clouds.bmp"); // Terrain moet ingeladen worden
}


Scene::~Scene()
{
}

void Scene::createEntity(Entities sort){
	Entity *newEntity;

	switch (sort)
	{
	case(CAMERA) :
		newEntity = new Camera();
		break;
	case(MODEL) :
		newEntity = new Model();
		break;
	default:
		Logger::getInstance().log(WARNING, "Entity fout");
		break;
	}

	entities.push_back(newEntity);
};

void deleteEntity(Entity* entity){
	// destroy en delete meegegeven entity uit lijst
};

std::vector<Entity*> Scene::getEntities(){
	return entities;
};
