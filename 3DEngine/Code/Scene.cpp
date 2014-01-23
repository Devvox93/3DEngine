#include "Scene.h"
#include "Model.h"
#include "Camera.h"
#include "Logger.h"

Scene::Scene(std::string path, ResourceManager* resourceManager)
{
	models = std::vector<Entity*>();
	cameras = std::vector<Entity*>();
	sceneFile = resourceManager->getSceneFile(path);
	readSceneFile(sceneFile, resourceManager);
};

Scene::~Scene()
{
};

void Scene::deleteModel(Entity* entity){
	// destroy and delete passed entity from list
};

void Scene::updateEntities()
{
	for each (Entity* camera in cameras)
	{
		camera->update();
	}
	for each (Entity* model in models)
	{
		model->update();
	}
};

std::vector<Entity*> Scene::getModels()
{
	return models;
};

void Scene::addCamera(Entity* camera)
{
	cameras.push_back(camera);
};

void Scene::setActiveCamera(int camera)
{
	activeCamera = camera;
};

Entity* Scene::getActiveCamera()
{
	return cameras[activeCamera];
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
	for (unsigned int i = 0; i < sceneFile->size(); ++i)
	{
		std::string infoString = sceneFile->at(i);

		size_t colon = infoString.find_first_of(":");

		std::string lineType = infoString.substr(0, colon);
		std::string lineInfo = infoString.substr(colon + 1, infoString.size() - colon - 1);

		if (lineType.compare("skybox") == 0)
		{
			std::ifstream file(lineInfo);
			if (file)
			{
				skybox = new Skybox(lineInfo, resourceManager);
			}
		}
		else if (lineType.compare("heightmap") == 0)
		{
			size_t comma = lineInfo.find_first_of(",");

			std::string heightmap = lineInfo.substr(0, comma);
			std::string terrainTexture = lineInfo.substr(comma + 1, lineInfo.size()-colon-1);

			std::ifstream fileHeightmap(heightmap);
			std::ifstream fileTerrainTexture(terrainTexture);
			if (fileHeightmap && fileTerrainTexture)
			{
				terrain = new Terrain(heightmap, terrainTexture, resourceManager);
			}
		}
		else if (lineType.compare("entity") == 0)
		{
			size_t nameComma = lineInfo.find_first_of(",");
			std::string xResourceName = lineInfo.substr(0, nameComma);

			std::ifstream fileResource(xResourceName);
			if (fileResource)
			{
				size_t positionXComma = lineInfo.find(",", nameComma + 1);
				size_t positionYComma = lineInfo.find(",", positionXComma + 1);
				size_t positionZComma = lineInfo.find(",", positionYComma + 1);
				size_t yawComma = lineInfo.find(",", positionZComma + 1);
				size_t pitchComma = lineInfo.find(",", yawComma + 1);
				size_t rollComma = lineInfo.find(",", pitchComma + 1);
				size_t scaleXComma = lineInfo.find(",", rollComma + 1);
				size_t scaleYComma = lineInfo.find(",", scaleXComma + 1);

				std::string positionX = lineInfo.substr(nameComma + 1, positionXComma - nameComma - 1);
				std::string positionY = lineInfo.substr(positionXComma + 1, positionYComma - positionXComma - 1);
				std::string positionZ = lineInfo.substr(positionYComma + 1, positionZComma - positionYComma - 1);
				std::string yaw = lineInfo.substr(positionZComma + 1, yawComma - positionZComma - 1);
				std::string pitch = lineInfo.substr(yawComma + 1, pitchComma - yawComma - 1);
				std::string roll = lineInfo.substr(pitchComma + 1, rollComma - pitchComma - 1);
				std::string scaleX = lineInfo.substr(rollComma + 1, scaleXComma - rollComma - 1);
				std::string scaleY = lineInfo.substr(scaleXComma + 1, scaleYComma - scaleXComma - 1);
				std::string scaleZ = lineInfo.substr(scaleYComma + 1, infoString.size() - scaleYComma - 1);

				float positionXFloat = (float)atof(positionX.c_str());
				float positionYFloat = (float)atof(positionY.c_str());
				float positionZFloat = (float)atof(positionZ.c_str());
				float yawFloat = (float)atof(yaw.c_str());
				float pitchFloat = (float)atof(pitch.c_str());
				float rollFloat = (float)atof(roll.c_str());
				float scaleXFloat = (float)atof(scaleX.c_str());
				float pscaleYFloat = (float)atof(scaleY.c_str());
				float scaleZFloat = (float)atof(scaleZ.c_str());

			
				models.push_back(new Model((XResource*)resourceManager->getResource(xResourceName), positionXFloat, positionYFloat, positionZFloat, yawFloat, pitchFloat, rollFloat, scaleXFloat, pscaleYFloat, scaleZFloat));
			}
		}
	}
};