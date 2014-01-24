#include "NoobKernel.h"
#include "ExpertKernel.h"

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

NoobKernel::NoobKernel()
{
};

NoobKernel::~NoobKernel()
{
	delete renderer;
	delete sManager;
	delete wManager;
	delete iManager;
	delete rManager;
	delete cam2;
};

ExpertKernel::ExpertKernel()
{
};

ExpertKernel::~ExpertKernel()
{
	delete renderer;
	delete sManager;
	delete wManager;
	delete iManager;
	delete rManager;
};

bool ExpertKernel::createRenderer(RendererType type)
{
	switch (type)
	{
	case DirectX:
		renderer = new DirectXRenderer();
		if (renderer)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	default:
		return false;
	}
}

bool ExpertKernel::createInputManager()
{
	iManager = new InputManager();
	if (iManager)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ExpertKernel::createSceneManager()
{
	sManager = new SceneManager();
	if (sManager)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ExpertKernel::createWindowManager()
{
	wManager = new WindowManager(sManager);
	if (wManager)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ExpertKernel::createResourceManager()
{
	rManager = new ResourceManager();
	rManager->setD3DDevice(((DirectXRenderer *)renderer)->getD3DDevice());
	if (rManager)
	{
		return true;
	}
	else
	{
		return false;
	}
}

InputManager* ExpertKernel::getInputManager()
{
	return iManager;
}

SceneManager* ExpertKernel::getSceneManager()
{
	return sManager;
}

WindowManager* ExpertKernel::getWindowManager()
{
	return wManager;
}

ResourceManager* ExpertKernel::getResourceManager()
{
	return rManager;
}

Renderer* ExpertKernel::getRenderer()
{
	return renderer;
}

void NoobKernel::run(int screenWidth, int screenHeight, std::string scenefile)
{
	int width = screenWidth;
	int height = screenHeight;

	renderer = new DirectXRenderer();
	renderer->Initialize(width, height);
	sManager = new SceneManager();
	wManager = new WindowManager(sManager);
	iManager = new InputManager();

	cam2 = new Camera2();
	rManager = new ResourceManager;
	rManager->setD3DDevice(((DirectXRenderer *)renderer)->getD3DDevice());

	wManager->newWindow(renderer, 10, 10, width, height);

	sManager->createScene(rManager, scenefile, wManager->getLastWindow()->_hwnd, renderer);
	Scene* scene = sManager->getScene(wManager->getLastWindow()->_hwnd);
	scene->addCamera(cam2);
	scene->setActiveCamera(0);

	iManager->initialize(GetModuleHandle(NULL), wManager->getLastWindow()->_hwnd, width, height);

	iManager->addListenerToKeyboard(cam2);
	iManager->addListenerToMouse(cam2);
	iManager->addListenerToJoystick(cam2);
	
	while (wManager->hasActiveWindow())
	{
		wManager->updateWindows();
		iManager->frame();
	}
};