#include "Scene.h"
#include <vector>

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void createScene();
	void deleteScene();
private:
	std::vector<Scene> scenes;
};

