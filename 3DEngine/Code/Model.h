/*!
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
	/*!
		Creates a model with given attributes.

		@param _model: A pointer to the XResource.
		@param _positionX: The position on the X-axis.
		@param _positionY: The position on the Y-axis.
		@param _positionZ: The position on the Z-axis.
		@param _yaw: The horizontal rotation.
		@param _pitch: The vertical rotation.
		@param _roll: The rolling rotation.
		@param _scaleX: The scale in the X-axis.
		@param _scaleY: The scale in the Y-axis.
		@param _scaleZ: The scale in the Z-axis.
	*/
	Model(XResource* _model, float _positionX, float _positionY, float _positionZ, float _yaw, float _pitch, float _roll, float _scaleX, float _scaleY, float _scaleZ);
	~Model();

	/*!
		Updates the model.
	*/
	void update();

	/*!
		Returns a pointer.

		@return XResource: The XResource of the model.
	*/
	XResource* getModel();
private:
	XResource* model;
};
#endif