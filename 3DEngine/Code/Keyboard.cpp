#pragma warning(disable : 4996)

#include "Keyboard.h"
#include "InputManager.h"
#include "Logger.h"

//// Define the keys we want to use
//#define KEYDOWN (name, key) (name[key] & 0x80)
//#define KEYUP (name, key) (name[key] & 0x80)

/**
* Function:	Keyboard::Keyboard(...)
* Description:	Keyboard constructor
*/
Keyboard::Keyboard(IDirectInputDevice8* argDevice)
{
	keyboard = argDevice;
	keyboardListeners = std::vector<KeyboardListener*>();
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
	//Logger::getInstance().log(INFO, "Processing keyboard input");
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

