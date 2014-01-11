#ifndef _SCENE_H_
#define _SCENE_H_

#include "Entity.h"
#include "Terrain.h"
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
	std::vector<Entity*> getEntities();
private:
	Terrain *terrain;
	std::vector<Entity*> entities;
};

#endif