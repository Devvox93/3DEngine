/*
3D Engine
Xresource.h
Purpose: Loads X resources.

@author Patrick, Nick, Robert, Jordi
@version 1.0
*/

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