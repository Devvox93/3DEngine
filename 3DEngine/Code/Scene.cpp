#include "Scene.h"
#include "Model.h"
#include "Camera.h"
#include "Logger.h"

Scene::Scene(char* path, ResourceManager* resourceManager)
{
	entities = std::vector<Entity*>();
	sceneFile = resourceManager->getSceneFile(path);
	//terrain = new Terrain("clouds.bmp", "tex.bmp", resourceManager); // Terrain moet ingeladen worden
	//skybox = new Skybox("skybox.jpg", resourceManager);
	createEntity(MODEL, resourceManager);
	readSceneFile(sceneFile, resourceManager);
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

void Scene::readSceneFile(std::vector<std::string>* sceneFile, ResourceManager *resourceManager)
{
	std::string stringTerrainPath = sceneFile->at(0);
	char* terrainPath = new char[stringTerrainPath.length()+1];
	strcpy_s(terrainPath, stringTerrainPath.length()+1, stringTerrainPath.c_str());

	std::string stringTerrainTexturePath = sceneFile->at(1);
	char* terrainTexturePath = new char[stringTerrainTexturePath.length()+1];
	strcpy_s(terrainTexturePath, stringTerrainTexturePath.length()+1, stringTerrainTexturePath.c_str());
	terrain = new Terrain(terrainPath, terrainTexturePath, resourceManager);
	
	std::string stringSkyboxTexturePath = sceneFile->at(2);
	char* skyboxTexturePath = new char[stringSkyboxTexturePath.length()+1];
	strcpy_s(skyboxTexturePath, stringSkyboxTexturePath.length()+1, stringSkyboxTexturePath.c_str());
	skybox = new Skybox(skyboxTexturePath, resourceManager);

	for (int i = 4; i <= sceneFile->size(); ++i)
	{
		Logger::getInstance().log(INFO, "deze bestaat niet");
	}
};