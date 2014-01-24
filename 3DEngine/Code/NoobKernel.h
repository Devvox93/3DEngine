/*!
	3D Engine
	NoobKernel.h
	Purpose: Manages all managers and is the main interface to our engine, noob version.

	@author Patrick, Nick, Robert, Jordi
	@version 1.0
*/

#include "Renderer.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "Camera2.h"
#include <array>

class NoobKernel
{
public:
	NoobKernel();
	~NoobKernel();

	/*!
		Function that initiates all parts of the engine.

		@param screenWidth: The width of the window that will be created.
		@param screenHeight: The height of the window that will be created.
		@param scenefile: The name of the scenefile (
	*/
	void run(int screenWidth, int screenHeight, std::string scenefile);

	/*!
		Method that performs actions based on keyboard input.

		@param keyboardState: Array that contains the state of all keys on the keyboard.
	*/
	void useKeyboardInput(std::array<unsigned char, 256> keyboardState);
private:
	Renderer *renderer;
	WindowManager *wManager;
	InputManager *iManager;
	SceneManager *sManager;
	Camera2 *cam2;
	ResourceManager *rManager;
};