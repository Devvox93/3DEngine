/*!
	3D Engine
	Scene.h
	Purpose: Keeps information about a scene.

	@author Patrick, Nick, Robert, Jordi
	@version 1.0
*/

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
	/*!
		Creates a scene from a file on disk.

		@param path: The path to the scene file on disk.
		@param rsm: A pointer to the resource manager to load the scene file.
	*/
	Scene(std::string path, ResourceManager* rsm);
	~Scene();

	/*!
		Deletes a model from scene.

		@param entity: The entity that needs to be deleted.
	*/
	void deleteModel(Entity* entity);

	/*!
		Updates the information of the entities.
	*/
	void updateEntities();

	/*!
		Returns a vector.

		@return vector<Entity*>: A vector with all models present in scene.
	*/
	std::vector<Entity*> getModels();

	/*!
		Adds a camera to the scene.

		@param camera: The camera to be added.
	*/
	void addCamera(Entity* camera);

	/*!
		Sets which camera is the active one.

		@param camera: The number of the camera that needs to be set active.
	*/
	void setActiveCamera(int camera);

	/*!
		Returns a pointer.

		@return Entity*: A pointer to the active camera.
	*/
	Entity* getActiveCamera();

	/*!
		Returns a pointer.

		@return Terrain*: A pointer to the terrain.
	*/
	Terrain* getTerrain();

	/*!
		Returns a pointer.

		@return Skybox: A pointer tot the skybox.
	*/
	Skybox* getSkybox();

	/*!
		Reads a scenefile from disk.

		@param *sceneFile: A pointer to a string containing the filepath.
		@param *resourceManager: A pointer to the resource manager to load the file from disk.
	*/
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