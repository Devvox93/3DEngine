#define DIRECTINPUT_VERSION 0x0800

#include "InputManager.h"
#include "Keyboard.h"
#include "Logger.h"

InputManager::InputManager()
{
	directInput = 0;
	keyboard = 0;
	mouse = 0;
	myKeyboard = 0;
	myMouse = 0;
}


InputManager::~InputManager()
{
	// Release the mouse.
	myMouse->~Mouse();
	
	// Release the keyboard.
	myKeyboard->~Keyboard();

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

#pragma region keyboard
	// Initialize the direct input interface for the keyboard.
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Set the data format.  In this case since it is a keyboard we can use the predefined data format.
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return false;
	}

	// Set the cooperative level of the keyboard to not share with other programs.
	result = keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	// Now acquire the keyboard.
	result = keyboard->Acquire();
	if (FAILED(result))
	{
		return false;
	}
#pragma endregion

#pragma region mouse
	// Initialize the direct input interface for the mouse.
	result = directInput->CreateDevice(GUID_SysMouse, &mouse, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Set the data format for the mouse using the pre-defined mouse data format.
	result = mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		return false;
	}

	// Set the cooperative level of the mouse to share with other programs.
	result = mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	// Acquire the mouse.
	result = mouse->Acquire();
	if (FAILED(result))
	{
		return false;
	}
#pragma endregion

	myKeyboard = new Keyboard(keyboard);
	myMouse = new Mouse(mouse, argScreenWidth, argScreenHeight);

	return true;
}

bool InputManager::frame()
{
	bool result;

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
	//myMouse->processInput();

	return true;
}

Keyboard* InputManager::getKeyboard()
{
	return myKeyboard;
}