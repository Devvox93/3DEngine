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
	Scene(ResourceManager* rsm);
	~Scene();

	void createEntity(Entities sort, ResourceManager* rsm);
	void deleteEntity(Entity* entity);
	void loadEntities();
	void render();
	void updateEntities();
	std::vector<Entity*> getEntities();
	Terrain* getTerrain();
	Skybox* getSkybox();
private:
	Terrain *terrain;
	Skybox *skybox;
	std::vector<Entity*> entities;
};

#endif