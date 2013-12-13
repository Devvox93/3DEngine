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
	char keyBuffer[255];

	void saveReleaseDevice();
};

