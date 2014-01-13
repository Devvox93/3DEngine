#include "Kernel.h"
#include "Logger.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Camera.h"
#include <sstream>
#include "SceneManager.h"

Kernel::Kernel()
{
}

Kernel::~Kernel()
{

}

void Kernel::run()
{
	int width = 1280;
	int height = 720;

	renderer = new DirectXRenderer();
	sceneManager = new SceneManager();
	wManager = new WindowManager(sceneManager);
	iManager = new InputManager();

	Camera* cam = new Camera();

	renderer->Initialize(width, height);

	renderer->setActiveCamera(cam);

	sceneManager->createScene();

	wManager->newWindow(renderer, 10, 10, width, height);
	iManager->initialize(GetModuleHandle(NULL), wManager->getLastWindow()->_hwnd, 1024, 768);

	iManager->getKeyboard()->addKeyboardListener(this);
	iManager->getKeyboard()->addKeyboardListener(cam);
	iManager->getJoystick()->addJoystickListener(cam);
	
	while (wManager->hasActiveWindow())
	{
		wManager->updateWindows();
		iManager->frame();
	}
}

void Kernel::useKeyboardInput(std::array<unsigned char, 256> keyboardState)
{
	Logger::getInstance().log(INFO, "Input gebruikt ofzo");

	if (keyboardState[DIK_ESCAPE] & 0x80)
	{
		Logger::getInstance().log(INFO, "Afgesloten met Escape");
		exit(EXIT_SUCCESS);
	}
}