#define DIRECTINPUT_VERSION 0x0800

#include "InputManager.h"
#include "Keyboard.h"
#include "Logger.h"

InputManager::InputManager()
{
	directInput = 0;
	myKeyboard = 0;
	myMouse = 0;
	myJoystick = 0;
}


InputManager::~InputManager()
{
	// Release the mouse.
	myMouse->~Mouse();
	
	// Release the keyboard.
	myKeyboard->~Keyboard();

	// Release the joystick.
	myJoystick->~Joystick();

	// Release the main interface to direct input.
	if (directInput)
	{
		directInput->Release();
		directInput = 0;
	}
}

bool InputManager::initialize(HINSTANCE hinstance, HWND hwnd, int argScreenWidth, int argScreenHeight)
{
	HRESULT result;

	// Initialize the main direct input interface.
	result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, NULL);
	if (FAILED(result))
	{
		return false;
	}

	myKeyboard = new Keyboard(directInput, hwnd);
	myMouse = new Mouse(directInput, hwnd, argScreenWidth, argScreenHeight);
	myJoystick = new Joystick(directInput, hwnd);

	return true;
}

bool InputManager::frame()
{
	bool result;

	// Read the current state of the joystick.
	if (myJoystick->available)
	{
		result = myJoystick->read();
		if (!result)
		{
			return false;
		}
		myJoystick->processInput();
	}

	// Read the current state of the keyboard.
	result = myKeyboard->read();
	if (!result)
	{
		return false;
	}

	// Read the current state of the mouse.
	result = myMouse->read();
	if (!result)
	{
		return false;
	}

	// Process the changes in the mouse and keyboard.
	myKeyboard->processInput();
	myMouse->processInput();

	return true;
}

Keyboard* InputManager::getKeyboard()
{
	return myKeyboard;
}

Mouse* InputManager::getMouse()
{
	return myMouse;
}

Joystick* InputManager::getJoystick()
{
	return myJoystick;
}