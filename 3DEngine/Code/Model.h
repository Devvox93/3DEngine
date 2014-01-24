/*
3D Engine
Xresource.h
Purpose: Loads X resources.

@author Patrick, Nick, Robert, Jordi
@version 1.0
*/

#ifndef _MODEL_H_
#define _MODEL_H_

#include "Entity.h"
#include "XResource.h"

class Model : public Entity
{
public:
	Model(XResource* _model, float _positionX, float _positionY, float _positionZ, float _yaw, float _pitch, float _roll, float _scaleX, float _scaleY, float _scaleZ);
	~Model();
	void update();
	XResource* getModel();
private:
	XResource* model;
};
#endif