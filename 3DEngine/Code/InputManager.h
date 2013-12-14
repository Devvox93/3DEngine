#include "Dinput.h"
#include "windows.h"
#include "Keyboard.h"

class InputManager
{
public:
	InputManager();
	~InputManager();

	void initKeyboard();
	bool assignWindowToKeyboard(HWND argHwnd);
private:
	IDirectInput8 *dInput;
	HWND hwnd;
	Keyboard* keyboard;

	void saveReleaseDevice();
};

