#include "Kernel.h"
#include "Logger.h"

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
	for (int i = 5; i > 0; --i)
	{
		wManager->newWindow(renderer);
	}

	iManager->initialize(GetModuleHandle(NULL), wManager->getLastWindow()->_hwnd, 1024, 768);

	iManager->getKeyboard()->addKeyboardListener(this);

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