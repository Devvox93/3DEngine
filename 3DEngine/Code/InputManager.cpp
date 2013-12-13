#define DIRECTINPUT_VERSION 0x0800

#include "InputManager.h"
#include "Keyboard.h"

InputManager::InputManager()
{
	IDirectInputDevice8 *dDevice = NULL;

	//DirectInput8Create should be done only once in manager
	HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dInput, NULL);
	if FAILED(hr)
	{
		// error geven
	}

	hr = dInput->CreateDevice(GUID_SysKeyboard, &dDevice, NULL);
	if FAILED(hr)
	{
		saveReleaseDevice();
		// error geven
	}
	else
	{
		keyboard = new Keyboard(dDevice);
	}


}


InputManager::~InputManager()
{
	// release keyboard pointer
}

/**
* Function:
* Description:
*/
bool InputManager::assignWindowToKeyboard(HWND argHwnd)
{
	keyboard->assignWindow(argHwnd);
}

/**
* Function:	Keyboard::saveReleaseDevice()
* Description:	Cleaning up the mess left if a keyboard is lost
*/
void InputManager::saveReleaseDevice()
{
	if (dInput)
	{
		dInput->Release();
		dInput = NULL;
	}
}