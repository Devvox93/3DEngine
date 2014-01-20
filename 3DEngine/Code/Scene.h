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
	Scene(std::string path, ResourceManager* rsm);
	~Scene();

	void createEntity(Entities sort, ResourceManager* rsm);
	void deleteModel(Entity* entity);
	void loadEntities();
	void render();
	void updateEntities();
	std::vector<Entity*> getModels();
	void addCamera(Entity* camera);
	void setActiveCamera(int camera);
	Entity* getActiveCamera();
	Terrain* getTerrain();
	Skybox* getSkybox();
	void readSceneFile(std::vector<std::string> *sceneFile, ResourceManager *resourceManager);
	std::vector<std::string> *sceneFile;
private:
	Terrain *terrain;
	Skybox *skybox;
	std::vector<Entity*> models;
	std::vector<Entity*> cameras;
	int activeCamera;

};

#endif