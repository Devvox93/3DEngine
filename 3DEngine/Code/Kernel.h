#include "Renderer.h"
#include "WindowManager.h"
#include "InputManager.h"
#include <array>

class Kernel : KeyboardListener
{
public:
	Kernel();
	~Kernel();

	void run();

	void useKeyboardInput(std::array<unsigned char, 256> keyboardState);
private:
	Renderer *renderer;
	WindowManager *wManager;
	InputManager *iManager;
};