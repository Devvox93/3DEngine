/*
	3D Engine
	ExpertKernel.h
	Purpose: Manages all managers and is the main interface to our engine, expert version.

	@author Patrick, Nick, Robert, Jordi
	@version 1.0
*/

#include "Renderer.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "Camera2.h"
#include <array>

enum RendererType { DirectX };

class ExpertKernel
{
public:
	ExpertKernel();
	~ExpertKernel();

	/*!
		Creates a renderer.

		@return bool: Returns true if the creation succeeded.
		@param type: The type of renderer to be used (DirectX or OpenGL).
	*/
	bool createRenderer(RendererType type);

	/*!
		Creates an inputmanager.

		@return bool: Returns true if the creation succeeded.
	*/
	bool createInputManager();

	/*!
		Creates a scenemanager.

		@return bool: Returns true if the creation succeeded.
	*/
	bool createSceneManager();

	/*!
		Creates a windowmanager.

		@return bool: Returns true if the creation succeeded.
	*/
	bool createWindowManager();

	/*!
		Creates a resourcemanager.

		@return bool: Returns true if the creation succeeded.
	*/
	bool createResourceManager();

	/*!
		Returns a pointer.

		@return InputManager: Returns a pointer to the manager.
	*/
	InputManager* getInputManager();

	/*!
		Returns a pointer.

		@return SceneManager: Returns a pointer to the manager.
	*/
	SceneManager* getSceneManager();

	/*!
		Returns a pointer.

		@return WindowManager: Returns a pointer to the manager.
	*/
	WindowManager* getWindowManager();

	/*!
		Returns a pointer.

		@return ResourceManager: Returns a pointer to the manager.
	*/
	ResourceManager* getResourceManager();

	/*!
		Returns a pointer.

		@return Renderer: Returns a pointer to the renderer.
	*/
	Renderer* getRenderer();

	/*
		Method that performs actions based on keyboard input.

		@param keyboardState: Array that contains the state of all keys on the keyboard.
	*/
	void useKeyboardInput(std::array<unsigned char, 256> keyboardState);
private:
	Renderer* renderer;
	WindowManager* wManager;
	InputManager* iManager;
	SceneManager* sManager;
	ResourceManager* rManager;
};