#include "Entity.h"
#include "XResource.h"

class Model : public Entity
{
public:
	Model();
	~Model();

	void update();
	XResource* model;
};

