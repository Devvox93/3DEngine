#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <d3dx9.h>

struct TripleFloat
{
	float x, y, z;
};

class Entity
{
public:
	Entity();
	~Entity();
	virtual void update() = 0;
	void setPosition(float x, float y, float z);
	void setRotation(float yaw, float pitch, float roll);
	void setScale(float scaleX, float scaleY, float scaleZ);
	TripleFloat getPosition();
	TripleFloat getRotation();
	TripleFloat getScale();
	D3DXMATRIXA16 finalMatrix;
protected:
	float x, y, z;
	float yaw, pitch, roll;
	float scaleX, scaleY, scaleZ;
	D3DXMATRIXA16 positionMatrix, rotationMatrix, scaleMatrix;
	void multiplyMatrices();
private:
};
#endif
