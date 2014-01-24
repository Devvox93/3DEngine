#include "Kernel.h"
#include "Logger.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Resource.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Camera2.h"
#include <sstream>
#include "SceneManager.h"

Kernel::Kernel()
{
};

Kernel::~Kernel()
{
	delete renderer;
	delete sManager;
	delete wManager;
	delete iManager;
	delete rManager;
	delete cam;
	delete cam2;	
};

void Kernel::run()
{
	int width = 1280;
	int height = 720;

	renderer = new DirectXRenderer();
	renderer->Initialize(width, height);
	sManager = new SceneManager();
	wManager = new WindowManager(sManager);
	iManager = new InputManager();

	cam = new Camera();
	cam2 = new Camera2();
	rManager = new ResourceManager;
	rManager->setD3DDevice(((DirectXRenderer *)renderer)->getD3DDevice());
	rManager->PrintMap();

	wManager->newWindow(renderer, 10, 10, width, height);

<<<<<<< HEAD
<<<<<<< HEAD
	sceneManager->createScene(rsManager, "scene one.txt", wManager->getLastWindow()->_hwnd, renderer);
	Scene* scene = sceneManager->getScene(wManager->getLastWindow()->_hwnd);
=======
	sManager->createScene(rManager, "default.txt", wManager->getLastWindow()->_hwnd, renderer);
	Scene* scene = sManager->getScene(wManager->getLastWindow()->_hwnd);
>>>>>>> 04ac3ee... Destructors (patrick houdt van mannen.)
=======
	sManager->createScene(rManager, "scene one.txt", wManager->getLastWindow()->_hwnd, renderer);
	Scene* scene = sManager->getScene(wManager->getLastWindow()->_hwnd);
>>>>>>> b5be66274fd88ea8db96b62012391e3c9f26537f
	scene->addCamera(cam);
	scene->addCamera(cam2);
	scene->setActiveCamera(1);

	iManager->initialize(GetModuleHandle(NULL), wManager->getLastWindow()->_hwnd, width, height);

	iManager->addListenerToKeyboard(this);
	iManager->addListenerToKeyboard(cam);
	iManager->addListenerToMouse(cam);
	iManager->addListenerToJoystick(cam);

	iManager->addListenerToKeyboard(cam2);
	iManager->addListenerToMouse(cam2);
	iManager->addListenerToJoystick(cam2);
	
	while (wManager->hasActiveWindow())
	{
		wManager->updateWindows();
		iManager->frame();
	}
};

void Kernel::useKeyboardInput(std::array<unsigned char, 256> keyboardState)
{
	if (keyboardState[DIK_ESCAPE] & 0x80)
	{
		Logger::getInstance().log(INFO, "Afgesloten met Escape");
		exit(EXIT_SUCCESS);
	}
};
