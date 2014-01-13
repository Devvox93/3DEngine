#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_


#include "Dinput.h"
#include "windows.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

class InputManager
{
public:
	InputManager();
	~InputManager();

	bool initialize(HINSTANCE, HWND, int screenWidth, int screenHeight);
	bool frame();
	Keyboard* getKeyboard();
	Mouse* getMouse();
	Joystick* getJoystick();
private:

	IDirectInput8* directInput;
	Keyboard* myKeyboard;
	Mouse* myMouse;
	Joystick* myJoystick;
};

#endif