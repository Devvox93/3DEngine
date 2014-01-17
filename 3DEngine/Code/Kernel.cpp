#include "Kernel.h"
#include "Logger.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Resource.h"
#include "ResourceManager.h"
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
	renderer->Initialize(width, height);
	sceneManager = new SceneManager();
	wManager = new WindowManager(sceneManager);
	iManager = new InputManager();

	Camera* cam = new Camera();
	ResourceManager *rsManager = new ResourceManager;
	rsManager->g_pd3dDevice = &((DirectXRenderer *)renderer)->g_pd3dDevice;
	rsManager->getResource("clouds.bmp");
	rsManager->getResource("btest.bmp");
	rsManager->getResource("test.bmp");
	rsManager->getResource("car.X");

	rsManager->PrintMap();

	
	renderer->setActiveCamera(cam);

	std::vector<std::string>* sceneFile = rsManager->getSceneFile("default.txt");

	sceneManager->createScene(rsManager, "default.txt");

	wManager->newWindow(renderer, 10, 10, width, height);
	iManager->initialize(GetModuleHandle(NULL), wManager->getLastWindow()->_hwnd, 1024, 768);

	iManager->getKeyboard()->addKeyboardListener(this);
	iManager->getKeyboard()->addKeyboardListener(cam);
	iManager->getMouse()->addMouseListener(cam);
	iManager->getJoystick()->addJoystickListener(cam);
	
	while (wManager->hasActiveWindow())
	{
		wManager->updateWindows();
		iManager->frame();
	}
}

void Kernel::useKeyboardInput(std::array<unsigned char, 256> keyboardState)
{
	if (keyboardState[DIK_ESCAPE] & 0x80)
	{
		Logger::getInstance().log(INFO, "Afgesloten met Escape");
		exit(EXIT_SUCCESS);
	}
}