/*
	3D Engine
	Kernel.h
	Purpose: Manages all managers and is the main interface to our engine.

	@author Patrick, Nick, Robert, Jordi
	@version 1.0
*/

#include "Renderer.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "Camera2.h"
#include <array>

class Kernel : KeyboardListener
{
public:
	Kernel();
	~Kernel();

	/*
		Function that initiates all parts of the engine.
	*/
	void run();

	/*
		Method that performs actions based on keyboard input.

		@param keyboardState: Array that contains the state of all keys on the keyboard.
	*/
	void useKeyboardInput(std::array<unsigned char, 256> keyboardState);
private:
	Renderer *renderer;
	WindowManager *wManager;
	InputManager *iManager;
	SceneManager *sManager;
	Camera *cam;
	Camera2 *cam2;
	ResourceManager *rManager;

};