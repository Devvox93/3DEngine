#include "WindowManager.h"
#include <string>
#include "Logger.h"
#include <sstream>

WindowManager::WindowManager(SceneManager *sManager)
{
	sceneManager = sManager;
};

WindowManager::~WindowManager()
{
};

void WindowManager::newWindow(Renderer *renderer, int x, int y, int width, int height)
{
	DirectXWindow *window = new DirectXWindow(renderer);
	HWND hwnd = window->Create(x, y, width, height, NULL, NULL, NULL);

	if (hwnd == NULL)
	{
		Logger::getInstance().log(CRITICAL, "Could not make window!");
		return;
	}

	WindowList *list = new WindowList();

	renderer->initTerrain(sceneManager->getScene()->getTerrain());
	renderer->initSkybox(sceneManager->getScene()->getSkybox());

	list->window = window;
	list->next = windows;
	windows = list;
};

void WindowManager::updateWindows()
{
	MSG Msg;
	while (PeekMessage(&Msg, NULL, 0U, 0U, true) > 0)//if there's more than one message, go through all of them.
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	WindowList *list = windows;
	while (list != NULL)//loop through all the windows so we can render them.
	{
		list->window->render(sceneManager->getScene());
		list = list->next;
	}
};

bool WindowManager::hasActiveWindow()
{
	WindowList *previous = NULL;
	WindowList *current = windows;
	while (current != NULL)
	{
		if (current->window->state == closed)
		{
			if (current == windows)//it's the current root
			{
				previous = current;
				current = current->next;
				windows = current;
				delete previous;
			}
			else 
			{
				WindowList *toDelete = current;
				previous->next = current->next;
				current = current->next;
				delete toDelete;
			}
		}
		else 
		{
			previous = current;
			current = current->next;
		}
	}
		
	if (windows != NULL)
	{
		return true;
	}
	return false;
};

Window* WindowManager::getLastWindow()
{
	return windows->window;
};