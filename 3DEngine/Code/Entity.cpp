#include "Entity.h"


Entity::Entity()
{
	x = y = z = 0.0f;
	yaw = pitch = roll = 0.0f;
	scaleX = 1.0f;
	scaleY = 1.0f;
	scaleZ = 1.0f;
	multiplyMatrices();
}


Entity::~Entity()
{
}

TripleFloat Entity::getPosition()
{
	return { x, y, z };
}

TripleFloat Entity::getRotation()
{
	return { yaw, pitch, roll };
}

TripleFloat Entity::getScale()
{
	return { scaleX, scaleY, scaleZ };
}

void Entity::update()
{

}

void Entity::setPosition(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
	D3DXMatrixTranslation(&positionMatrix, x, y, z);
	multiplyMatrices();
}

void Entity::setRotation(float _yaw, float _pitch, float _roll)
{
	yaw = _yaw;
	pitch = _pitch;
	roll = _roll;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);
	multiplyMatrices();
}

void Entity::setScale(float _scaleX, float _scaleY, float _scaleZ)
{
	scaleX = _scaleX;
	scaleY = _scaleY;
	scaleZ = _scaleZ;
	D3DXMatrixScaling(&scaleMatrix, scaleX, scaleY, scaleZ);
	multiplyMatrices();
}

void Entity::multiplyMatrices() 
{
	finalMatrix = positionMatrix;

	if (yaw != 0 || pitch != 0 || roll != 0) {
		D3DXMatrixMultiply(&finalMatrix, &positionMatrix, &rotationMatrix);
	}

	if (scaleX != 1 || scaleY != 1 || scaleZ != 1) {
		D3DXMatrixMultiply(&finalMatrix, &finalMatrix, &scaleMatrix);
	}
}