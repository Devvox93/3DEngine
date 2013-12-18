#ifndef _MOUSE_H_
#define _MOUSE_H_


#include "dinput.h"
#include "MouseListener.h"
#include <vector>

class Mouse
{
public:
	Mouse(IDirectInputDevice8* argDevice, int argScreenWidth, int argScreenHeight);
	~Mouse();

	void addMouseListener(MouseListener* argMouseListener);
	bool read();
	void processInput();
	void updateListeners();
	void getMouseLocation(int&, int&);
private:

	IDirectInputDevice8* mouse;
	DIMOUSESTATE mouseState;
	std::vector<MouseListener*> mouseListeners;
	int mouseX;
	int mouseY;
	int screenWidth;
	int screenHeight;
};

#endif