#include "Kernel.h"
#include "Logger.h"
<<<<<<< HEAD
=======
#include "WindowManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "HeightmapResource.h"


>>>>>>> 613b652cfa98fd973394bae7e19bebddd64d1c7d

Kernel::Kernel()
{
	Logger::getInstance().log(INFO, "Programma gestart :)");

	renderer = new Renderer();
	wManager = new WindowManager();
	iManager = new InputManager();
}

Kernel::~Kernel()
{

}

void Kernel::run()
{
<<<<<<< HEAD
=======
	Renderer *renderer = new Renderer();
	HeightmapResource *bla = new HeightmapResource("test.bmp");
	WindowManager *manager = new WindowManager();
>>>>>>> 613b652cfa98fd973394bae7e19bebddd64d1c7d
	for (int i = 5; i > 0; --i)
	{
		wManager->newWindow(renderer);
	}
<<<<<<< HEAD

	iManager->initialize(GetModuleHandle(NULL), wManager->getLastWindow()->_hwnd, 1024, 768);

	iManager->getKeyboard()->addKeyboardListener(this);

	while (wManager->hasActiveWindow())
=======
	
	InputManager *iManager = new InputManager();
	while (manager->hasActiveWindow())
>>>>>>> 613b652cfa98fd973394bae7e19bebddd64d1c7d
	{
		wManager->updateWindows();
		iManager->frame();
	}

<<<<<<< HEAD
}

void Kernel::useKeyboardInput(std::array<unsigned char, 256> keyboardState)
{
	Logger::getInstance().log(INFO, "Input gebruikt ofzo");

	if (keyboardState[DIK_ESCAPE] & 0x80)
	{
		Logger::getInstance().log(INFO, "Afgesloten met Escape");
		exit(EXIT_SUCCESS);
	}
=======
	system("pause");
	return 0;
>>>>>>> 613b652cfa98fd973394bae7e19bebddd64d1c7d
}