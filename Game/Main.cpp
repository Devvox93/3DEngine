#include "NoobKernel.h"
#include "ExpertKernel.h"
#include <Camera2.h>

int main()
{
	NoobKernel* kernel = new NoobKernel();

	kernel->run(1280, 720, "scene one.txt");

	system("pause");

	ExpertKernel* kernel2 = new ExpertKernel();
	kernel2->createRenderer(DirectX);
	kernel2->getRenderer()->Initialize(1280, 720);
	kernel2->createSceneManager();
	kernel2->createWindowManager();
	kernel2->createResourceManager();
	kernel2->createInputManager();

	kernel2->getWindowManager()->newWindow(kernel2->getRenderer(), 10, 10, 1280, 720);
	kernel2->getSceneManager()->createScene(kernel2->getResourceManager(), "scene one.txt", kernel2->getWindowManager()->getLastWindow()->_hwnd, kernel2->getRenderer());
	
	kernel2->getInputManager()->initialize(GetModuleHandle(NULL), kernel2->getWindowManager()->getLastWindow()->_hwnd, 1280, 720);

	Camera2* cam2 = new Camera2();

	kernel2->getInputManager()->addListenerToKeyboard(cam2);
	kernel2->getInputManager()->addListenerToMouse(cam2);
	kernel2->getInputManager()->addListenerToJoystick(cam2);
	
	Scene* scene = kernel2->getSceneManager()->getScene(kernel2->getWindowManager()->getLastWindow()->_hwnd);
	scene->addCamera(cam2);
	scene->setActiveCamera(0);

	while (kernel2->getWindowManager()->hasActiveWindow())
	{
		kernel2->getWindowManager()->updateWindows();
		kernel2->getInputManager()->frame();
	}

	system("pause");

	return 0;
}