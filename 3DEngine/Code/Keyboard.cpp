#include "Keyboard.h"
#include "Logger.h"

#define KEYDOWN(name, key) (name[key] & 0x80)

/**
* Function:	Keyboard::Keyboard(...)
* Description:	Keyboard constructor
*/
Keyboard::Keyboard(IDirectInputDevice8 *argDDevice)
{
	dDevice = argDDevice;

	HRESULT hr = dDevice->SetDataFormat(&c_dfDIKeyboard);
	if FAILED(hr)
	{
		saveReleaseDevice();
		// error geven
	}
}


/**
* Function:	Keyboard::~Keyboard()
* Description:	Keyboard destructor
*/
Keyboard::~Keyboard()
{

}


/**
* Function:	Keyboard::ProcessKBInput(...)
* Description:	Method to see if the keyboardbuffer can be red or that a aquire is needed
* @ param argIsToggle
*	 Boolean to see if the key that is pressed a togglebutton is
* @ param argKeyIsPressed
*	 Byte containing the key that must be checked
*/
bool Keyboard::processKBInput(byte argKeyIsPressed)
{
	if (!SUCCEEDED(dDevice->Poll()))
	{
		doAcquire();
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
		Logger::getInstance().log(INFO, "Key down is pressed.");
		return true;
	}
}

/**
* Function:	Keyboard::DoAcquire()
* Description:	Aquiring the device, multiple times to make sure it gets it
*/
bool Keyboard::doAcquire()
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

/**
* Function:	
* Description:	
*/
bool Keyboard::assignWindow(HWND argHwnd)
{
	HRESULT hr = dDevice->SetCooperativeLevel(argHwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	if FAILED(hr)
	{
		saveReleaseDevice();
		return false;
	}
}

/**
* Function:	Keyboard::saveReleaseDevice()
* Description:	Cleaning up the mess left if a keyboard is lost
*/
void Keyboard::saveReleaseDevice()
{
	if (dDevice)
	{
		dDevice->Unacquire();
		dDevice->Release();
		dDevice = NULL;
	}
}
