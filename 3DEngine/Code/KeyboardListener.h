/*
3D Engine
Xresource.h
Purpose: Loads X resources.

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
	virtual void useKeyboardInput(std::array<unsigned char, 256> keyboardState) = 0;
};
#endif