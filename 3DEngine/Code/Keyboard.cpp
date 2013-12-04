#include "Keyboard.h"

#define KEYDOWN(name, key) (name[key] & 0x80) 

/**
* Function:	Keyboard::Keyboard()
* Description:	Empty keyboard constructor
*/
Keyboard::Keyboard()
{

}

/**
* Function:	Keyboard::Keyboard(...)
* Description:	Keyboard constructor
* @ param hWnd:
*   Pointer to windowHandle, used to set the "SetCooperativeLevel"
*/
Keyboard::Keyboard(HWND argHwnd)
{
	dInput = NULL;
	dDevice = NULL;
	hwnd = argHwnd;

	InitKeyboard();
}


/**
* Function:	Keyboard::~Keyboard()
* Description:	Keyboard destructor
*/
Keyboard::~Keyboard()
{

}


/**
* Function:	Keyboard::InitKeyboard()
* Description:	initializing the keyboard (creating the device and setting the coopertive level)
*/
bool Keyboard::InitKeyboard()
{
	//DirectInput8Create should be done only once in manager
	HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dInput, NULL);
	if FAILED(hr)
	{
		return false;
	}

	hr = dInput->CreateDevice(GUID_SysKeyboard, &dDevice, NULL);
	if FAILED(hr)
	{
		SaveReleaseDevice();
		return false;
	}

	hr = dDevice->SetDataFormat(&c_dfDIKeyboard);
	if FAILED(hr)
	{
		SaveReleaseDevice();
		return false;
	}

	hr = dDevice->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	if FAILED(hr)
	{
		SaveReleaseDevice();
		return false;
	}

	return true;
}

/**
* Function:	Keyboard::saveReleaseDevice()
* Description:	Cleaning up the mess left if a keyboard is lost
*/
void Keyboard::SaveReleaseDevice()
{
	if (dInput)
	{
		if (dDevice)
		{
			dDevice->Unacquire();
			dDevice->Release();
			dDevice = NULL;
		}
		dInput->Release();
		dInput = NULL;
	}
}


/**
* Function:	Keyboard::ProcessKBInput(...)
* Description:	Method to see if the keyboardbuffer can be red or that a aquire is needed
* @ param argIsToggle
*	 Boolean to see if the key that is pressed a togglebutton is
* @ param argKeyIsPressed
*	 Byte containing the key that must be checked
*/
bool Keyboard::ProcessKBInput(byte argKeyIsPressed)
{
	if (!SUCCEEDED(dDevice->Poll()))
	{
		DoAcquire();
	}

	dDevice->GetDeviceState(sizeof(keyBuffer), (LPVOID)&keyBuffer);

	// Check if keybuffer contains given key
	int pressed = KEYDOWN(keyBuffer, argKeyIsPressed);

	// pressed == 0 or 128 (0x80); meaning false or true
	if (pressed == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

/**
* Function:	Keyboard::DoAcquire()
* Description:	Aquiring the device, multiple times to make sure it gets it
*/
bool Keyboard::DoAcquire()
{

	int times = 5;
	for (int i = 0; i < times; i++)
	{
		if (SUCCEEDED(dDevice->Acquire()))
		{
			return true;
		}
	}
	return false;
}
