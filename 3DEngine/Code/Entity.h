/*!
	3D Engine
	Entity.h
	Purpose: Keeps track of the position, rotation and scaling of entities.

	@author Patrick, Nick, Robert, Jordi
	@version 1.0
*/

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <d3dx9.h>
#include "Defines.h"

class Entity
{
public:
	Entity();
	~Entity();

	/*!
		 Abstract method that updates the entities.
	*/
	virtual void update() = 0;

	/*!
		 Sets the position of the entity.

		@param x: The position on the X-axis.
		@param y: The position on the Y-axis.
		@param z: The position on the Z-axis.
	*/
	void setPosition(float x, float y, float z);

	/*!
		 Sets the rotation of the entity.

		@param yaw: The horizontal rotation.
		@param pitch: The vertical rotation.
		@param roll: The rolling rotation.
	*/
	void setRotation(float yaw, float pitch, float roll);

	/*!
		 Sets the scale of the entity.

		@param x: The scale in the X-axis.
		@param y: The scale in the Y-axis.
		@param z: The scale in the Z-axis.
	*/
	void setScale(float scaleX, float scaleY, float scaleZ);

	/*!
		 Returns a value.

		@param TripleFloat: The position, set in 3 floats.
	*/
	TripleFloat getPosition();

	/*!
		 Returns a value.

		@param TripleFloat: The rotation, set in 3 floats.
	*/
	TripleFloat getRotation();

	/*!
		 Returns a value.

		@param TripleFloat: The scale, set in 3 floats.
	*/
	TripleFloat getScale();

	D3DXMATRIXA16 finalMatrix;
	D3DXMATRIXA16 rotationMatrix;

protected:
	float x, y, z;
	float yaw, pitch, roll;
	float scaleX, scaleY, scaleZ;
	D3DXMATRIXA16 positionMatrix, scaleMatrix;

	/*!
		 Multiplies the matrices to change the positions etc.
	*/
	void multiplyMatrices();

private:
};
#endif
