#include "Model.h"

Model::Model(XResource* _model, float _positionX, float _positionY, float _positionZ, float _yaw, float _pitch, float _roll, float _scaleX, float _scaleY, float _scaleZ)
{
	model = _model;

	setPosition(_positionX, _positionY, _positionZ);
	setRotation(_yaw, _pitch, _roll);
	setScale(_scaleX, _scaleY, _scaleZ);
};


Model::~Model()
{
	delete model;
};

void Model::update()
{
};

XResource* Model::getModel()
{
	return model;
};