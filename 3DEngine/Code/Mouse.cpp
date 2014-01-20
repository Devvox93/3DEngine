#include "Mouse.h"

Mouse::Mouse(IDirectInput8* directInput, HWND hwnd, int argScreenWidth, int argScreenHeight)
{
	mouseListeners = std::vector<MouseListener*>();

	HRESULT result;

	// Store the screen size which will be used for positioning the mouse cursor.
	screenWidth = argScreenWidth;
	screenHeight = argScreenHeight;

	// Initialize the location of the mouse on the screen.
	mouseX = 0;
	mouseY = 0;

	// Initialize the direct input interface for the mouse.
	result = directInput->CreateDevice(GUID_SysMouse, &mouse, NULL);
	if (FAILED(result))
	{
		return;
	}

	// Set the data format for the mouse using the pre-defined mouse data format.
	result = mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		return;
	}

	// Set the cooperative level of the mouse to share with other programs.
	result = mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return;
	}

	// Acquire the mouse.
	result = mouse->Acquire();
	if (FAILED(result))
	{
		return;
	}
};

Mouse::~Mouse()
{
	if (mouse)
	{
		mouse->Unacquire();
		mouse->Release();
		mouse = 0;
	}
};

void Mouse::addMouseListener(MouseListener* argMouseListener)
{
	mouseListeners.push_back(argMouseListener);
};

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
};

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

	if (mouseState.lX != 0 || mouseState.lY != 0)
	{
		updateListeners();
	}
};

void Mouse::updateListeners()
{
	for each (MouseListener* current in mouseListeners)
	{
		current->useMouseInput(mouseState);
	}
};