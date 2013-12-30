#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include "windows.h"
#include "Dinput.h"
#include "JoystickListener.h"
#include <vector>
#include <array>

class Joystick
{
public:
	Joystick(IDirectInput8* argInterface, HWND hDlg);
	~Joystick();
	void addJoystickListener(JoystickListener* argJoystickListener);
	bool read();
	void processInput();
	void updateListeners();
private:
	IDirectInputDevice8* joystick;
	DIJOYSTATE2 joystickState;
	DIJOYSTATE2 joystickStateOld;
	std::vector<JoystickListener*> joystickListeners;
};
#endif