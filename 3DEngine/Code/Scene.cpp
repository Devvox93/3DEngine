#include "Scene.h"
#include "Model.h"
#include "Camera.h"

Scene::Scene()
{
	entities = std::vector<Entity>();
	ground = NULL; // Terrain moet ingeladen worden
}


Scene::~Scene()
{
}

void Scene::createEntity(Entities sort){
	Entity *newEntity;

	switch (sort)
	{
	case(Camera) :
		newEntity = new Camera();
		break;
	case(Model) :
		newEntity = new Model();
		break;
	default:
		newEntity = new Entity;
		break;
	}

	entities.push_back(*newEntity);
};

void deleteEntity(Entity* entity){
	// destroy en delete meegegeven entity uit lijst
};

std::vector<Entity> Scene::getEntities(){
	return entities;
};
