#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "windows.h"
#include "Dinput.h"

class Keyboard
{
public:
	Keyboard(IDirectInputDevice8 *argDDevice);
	~Keyboard();
	
private:
};

#endif