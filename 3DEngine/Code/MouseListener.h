#include "dinput.h"

class MouseListener
{
public:
	MouseListener();
	virtual ~MouseListener();

	virtual void useMouseInput(DIMOUSESTATE mouseState);
};