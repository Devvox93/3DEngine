/*
	3D Engine
	KeyboardListener.h
	Purpose: Interface to unify the way keyboard input is used.

	@author Patrick, Nick, Robert, Jordi
	@version 1.0
*/

#ifndef _KEYBOARDLISTENER_
#define _KEYBOARDLISTENER_

#include <array>

class KeyboardListener
{
public:
	KeyboardListener();
	virtual ~KeyboardListener();

	/*
		Abstract method which needs to be implemented with actions based on keyboard input.

		@param keyboardState: Array that contains the state of all keys on the keyboard.
	*/
	virtual void useKeyboardInput(std::array<unsigned char, 256> keyboardState) = 0;
};
#endif