#ifndef _SCENE_
#define _SCENE_

#include "Entity.h"
#include "Ground.h"
#include <vector>

class Scene
{
public:
	Scene();
	~Scene();

	void createEntity(Entities sort);
	void deleteEntity(Entity* entity);
	std::vector<Entity> getEntities();
private:
	Ground ground;
	std::vector<Entity> entities;
};

#endif