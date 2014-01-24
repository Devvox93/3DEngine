/*
	3D Engine
	JoystickListener.h
	Purpose: Interface to be implemented where joystick input is needed.

	@author Patrick, Nick, Robert, Jordi
	@version 1.0
*/

#ifndef _JOYSTICKLISTENER_
#define _JOYSTICKLISTENER_

#include <array>
#include <dinput.h>

class JoystickListener
{
public:
	JoystickListener();
	virtual ~JoystickListener();

	/*
		Method that performs actions based on joystick input.

		@param keyboardState: Array that contains the state of all buttons on the joystick.
	*/
	virtual void useJoystickInput(DIJOYSTATE2) = 0;
};
#endif