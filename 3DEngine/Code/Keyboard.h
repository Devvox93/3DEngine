#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "windows.h"
#include "Dinput.h"

class Keyboard
{
public:
	Keyboard(IDirectInputDevice8 *argDDevice);
	~Keyboard();
	
	bool processKBInput(byte argKeyIsPressed);
	bool doAcquire();
	bool assignWindow(HWND argHwnd);
private:
	IDirectInputDevice8 *dDevice;
	char keyBuffer[254];

	void saveReleaseDevice();
};

#endif