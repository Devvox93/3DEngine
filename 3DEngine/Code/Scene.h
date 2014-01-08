#ifndef _SCENE_
#define _SCENE_

#include "Entity.h"
#include "Terrain.h"
#include <vector>

enum Entities
{
	Camera, Model
};

class Scene
{
public:
	Scene();
	~Scene();

	void createEntity(Entities sort);
	void deleteEntity(Entity* entity);
	std::vector<Entity> getEntities();
private:
	Terrain terrain;
	std::vector<Entity> entities;
};

#endif