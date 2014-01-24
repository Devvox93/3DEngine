/*!
	3D Engine
	Camera2.h
	Purpose: Provide the ability to change the field of view.

	@author Patrick, Nick, Robert, Jordi
	@version 1.0
*/

#ifndef _CAMERA2_H_
#define _CAMERA2_H_

#include "Entity.h"
#include "KeyboardListener.h"
#include "MouseListener.h"
#include "JoystickListener.h"
class Camera2 : public Entity, public KeyboardListener, public MouseListener, public JoystickListener
{
public:
	Camera2();
	~Camera2();
	
	/*!
		Method that updates the position and rotation of all entities in the world.
	*/
	void update();

	/*!
		Method that sets the position and converts this to a position matrix.

		@param x: The position on the X-axis.
		@param y: The position on the Y-axis.
		@param z: The position on the Z-axis.
	*/
	void setPosition(float x, float y, float z);

	/*!
		Method that sets the rotation and converts this to a rotation matrix.

		@param yaw: The horizontal rotation.
		@param pitch: The vertical rotation.
		@param roll: The "rolling" rotation.
	*/
	void setRotation(float yaw, float pitch, float roll);

	/*!
		Method that sets the scale and converts this to a scale matrix.

		@param scaleX: The factor to stretch on the X-axis.
		@param scaleY: The factor to stretch on the Y-axis.
		@param scaleZ: The factor to stretch on the Z-axis.
	*/
	void setScale(float scaleX, float scaleY, float scaleZ);

	/*!
		Method that multiplies different matrices to create offset-matrices.
	*/
	void multiplyMatrices();

	/*!
		Method that returns the position of the camera.

		@return TripleFloat: 3 floats representing the position on the X, Y and Z-axis.
	*/
	TripleFloat getPosition();

	/*!
		Method that returns the rotation of the camera.

		@return TripleFloat: 3 floats representing the rotation over Yaw, Pitch and Roll.
	*/
	TripleFloat getRotation();

	/*!
		Method that returns the scale of the world.

		@return TripleFloat: 3 floats representing the factor of which the world must be scaled.
	*/
	TripleFloat getScale();

	/*!
		Method that performs actions based on keyboard input.

		@param keyboardState: Array that contains the state of all keys on the keyboard.
	*/
	void useKeyboardInput(std::array<unsigned char, 256> keyboardState);

	/*!
		Method that performs actions based on mouse input.

		@param mouseState: Array that contains the movement of the mouse.
	*/
	void useMouseInput(DIMOUSESTATE mouseState);

	/*!
		Method that performs actions based on joystick input.

		@param joystickState: Array that contains the state of all buttons on the joystick.
	*/
	void useJoystickInput(DIJOYSTATE2 joystickState);

private:
	float xMovement, yMovement, zMovement, yawMovement, pitchMovement, rollMovement, movementAngle, movementSpeed;
	float spinAroundCurrentAngle, spinAroundX, spinAroundZ, spinAroundRadius;
	bool spinning;
	void changeMovement();
};
#endif