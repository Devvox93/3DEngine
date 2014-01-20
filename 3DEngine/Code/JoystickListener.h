#ifndef _JOYSTICKLISTENER_
#define _JOYSTICKLISTENER_

#include <array>
#include <dinput.h>

class JoystickListener
{
public:
	JoystickListener();
	virtual ~JoystickListener();

	virtual void useJoystickInput(DIJOYSTATE2) = 0;
};
#endif