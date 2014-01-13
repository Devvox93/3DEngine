#ifndef _SCENE_H_
#define _SCENE_H_

#include "Entity.h"
#include "Terrain.h"
#include "Skybox.h"
#include <vector>

enum Entities
{
	CAMERA, MODEL
};

class Scene
{
public:
	Scene();
	~Scene();

	void createEntity(Entities sort);
	void deleteEntity(Entity* entity);
	void loadEntities();
	void render();
	void updateEntities();
	std::vector<Entity*> getEntities();
private:
	Terrain *terrain;
	Skybox *skybox;
	std::vector<Entity*> entities;
};

#endif