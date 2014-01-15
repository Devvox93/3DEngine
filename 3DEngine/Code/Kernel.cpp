#include "Kernel.h"
#include "Logger.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Resource.h"
#include "ResourceManager.h"
#include "Camera.h"
#include <sstream>

Kernel::Kernel()
{
	renderer = new DirectXRenderer();
	wManager = new WindowManager();
	iManager = new InputManager();
}

Kernel::~Kernel()
{

}

void Kernel::run()
{
	Renderer *renderer = new DirectXRenderer();
	WindowManager *manager = new WindowManager();
	Camera* cam = new Camera();
	ResourceManager *rsManager = new ResourceManager;
	
	rsManager->storeResource("clouds.bmp");
	rsManager->storeResource("btest.bmp");
	rsManager->storeResource("test.bmp");
	rsManager->storeResource("clouds3s.bmp");
	rsManager->storeResource("clouds.bmp");
	rsManager->storeResource("clouds.bmp");
	rsManager->storeResource("car2.x");
	rsManager->storeResource("car.x");
	rsManager->storeResource("car.x");
	rsManager->storeResource("car.x");
	rsManager->storeResource("car.x");

	rsManager->PrintMap();

	
	renderer->setActiveCamera(cam);

	wManager->newWindow(renderer, 10, 10, 1280, 720);
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