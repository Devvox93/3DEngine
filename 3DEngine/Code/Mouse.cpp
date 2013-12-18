#include "Mouse.h"

/**
* Function:	Mouse::Mouse()
* Description:	Empty mouse constructor
*/
Mouse::Mouse(IDirectInputDevice8* argDevice, int argScreenWidth, int argScreenHeight)
{
	mouse = argDevice;
	mouseListeners = std::vector<MouseListener*>();

	// Store the screen size which will be used for positioning the mouse cursor.
	screenWidth = argScreenWidth;
	screenHeight = argScreenHeight;

	// Initialize the location of the mouse on the screen.
	mouseX = 0;
	mouseY = 0;
}

/**
* Function:	Mouse::~Mouse()
* Description:	destructor of the mouse
*/
Mouse::~Mouse()
{
	if (mouse)
	{
		mouse->Unacquire();
		mouse->Release();
		mouse = 0;
	}
}

void Mouse::addMouseListener(MouseListener* argMouseListener)
{
	mouseListeners.push_back(argMouseListener);
}

bool Mouse::read()
{
	HRESULT result;


	// Read the mouse device.
	result = mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouseState);
	if (FAILED(result))
	{
		// If the mouse lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			mouse->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

void Mouse::processInput()
{
	// Update the location of the mouse cursor based on the change of the mouse location during the frame.
	mouseX += mouseState.lX;
	mouseY += mouseState.lY;

	// Ensure the mouse location doesn't exceed the screen width or height.
	if (mouseX < 0)
	{
		mouseX = 0;
	}
	else if (mouseY < 0)
	{
		mouseY = 0;
	}
	else if (mouseX > screenWidth)
	{
		mouseX = screenWidth;
	}
	else if (mouseY > screenHeight)
	{
		mouseY = screenHeight;
	}

	return;
}

void Mouse::updateListeners()
{
	for each (MouseListener* current in mouseListeners)
	{
		// TODO mouse state, nieuwe mouse location of mouseveranderingen meegeven
		//current->useMouseInput();
	}
}