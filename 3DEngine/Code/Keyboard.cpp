#pragma warning(disable : 4996)

#include "Keyboard.h"
#include "InputManager.h"
#include "Logger.h"

/**
* Function:	Keyboard::Keyboard(...)
* Description:	Keyboard constructor
*/
Keyboard::Keyboard(IDirectInput8* directInput, HWND hwnd)
{
	keyboardListeners = std::vector<KeyboardListener*>();

	HRESULT result;

	// Initialize the direct input interface for the keyboard.
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	if (FAILED(result))
	{
		return;
	}

	// Set the data format.  In this case since it is a keyboard we can use the predefined data format.
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return;
	}

	// Set the cooperative level of the keyboard to not share with other programs.
	result = keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result))
	{
		return;
	}

	// Now acquire the keyboard.
	result = keyboard->Acquire();
	if (FAILED(result))
	{
		return;
	}
}


/**
* Function:	Keyboard::~Keyboard()
* Description:	Keyboard destructor
*/
Keyboard::~Keyboard()
{
	if (keyboard)
	{
		keyboard->Unacquire();
		keyboard->Release();
		keyboard = 0;
	}
}

void Keyboard::addKeyboardListener(KeyboardListener* argKeyboardListener)
{
	keyboardListeners.push_back(argKeyboardListener);
}

bool Keyboard::read()
{
	HRESULT result;

	// Read the keyboard device.
	result = keyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);
	if (FAILED(result))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

void Keyboard::processInput()
{
	if (keyboardStateOld != keyboardState)
	{
		updateListeners();
	}

	std::copy(std::begin(keyboardState), std::end(keyboardState), std::begin(keyboardStateOld));
}

void Keyboard::updateListeners()
{
	for each (KeyboardListener* current in keyboardListeners)
	{
		current->useKeyboardInput(keyboardState);
	}
}

