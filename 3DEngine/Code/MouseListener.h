#ifndef _MOUSELISTENER_H_
#define _MOUSELISTENER_H_

#include "dinput.h"

class MouseListener
{
public:
	MouseListener();
	virtual ~MouseListener();

	virtual void useMouseInput(DIMOUSESTATE mouseState) = 0;
};
#endif