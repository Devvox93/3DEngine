#include "Dinput.h"
#include "windows.h"
#include "Keyboard.h"
#include "Mouse.h"

class InputManager
{
public:
	InputManager();
	~InputManager();

	bool initialize(HINSTANCE, HWND, int screenWidth, int screenHeight);
	bool frame();
	Keyboard* getKeyboard();
private:

	IDirectInput8* directInput;
	IDirectInputDevice8* keyboard;
	IDirectInputDevice8* mouse;
	Keyboard* myKeyboard;
	Mouse* myMouse;
};