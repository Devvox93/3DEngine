#include "Kernel.h"
#include "Logger.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "HeightmapResource.h"
#include "DirectXRenderer.h"
#include "ResourceManager.h"
#include "Camera.h"

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
	renderer->setActiveCamera(cam);

	wManager->newWindow(renderer, 10, 10, 1024, 1024);
	ResourceManager *rsManager = new ResourceManager();
	HeightmapResource *bla = new HeightmapResource("test.bmp");

	rsManager->storeResource("test.bmp");
	rsManager->storeResource("clouds.bmp");
	rsManager->storeResource("test.bmp");

	
	rsManager->PrintMap();
	iManager->initialize(GetModuleHandle(NULL), wManager->getLastWindow()->_hwnd, 1024, 768);

	iManager->getKeyboard()->addKeyboardListener(this);
	iManager->getKeyboard()->addKeyboardListener(cam);


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