#ifndef _SCENE_H_
#define _SCENE_H_

#include "Entity.h"
#include "Terrain.h"
#include "Skybox.h"
#include <vector>
#include "ResourceManager.h"

enum Entities
{
	CAMERA, MODEL
};

class Scene
{
public:
	Scene(char* path, ResourceManager* rsm);
	~Scene();

	void deleteModel(Entity* entity);
	void updateEntities();
	std::vector<Entity*> getModels();
	void addCamera(Entity* camera);
	void setActiveCamera(int camera);
	Entity* getActiveCamera();
	Terrain* getTerrain();
	Skybox* getSkybox();
	void readSceneFile(std::vector<std::string> *sceneFile, ResourceManager *resourceManager);
private:
	Terrain *terrain;
	Skybox *skybox;
	std::vector<Entity*> models;
	std::vector<Entity*> cameras;
	int activeCamera;
	std::vector<std::string> *sceneFile;
};
#endif