#include "WindowManager.h"
#include <string>
#include "Logger.h"
#include <sstream>

WindowManager::WindowManager()
{
}

WindowManager::~WindowManager()
{
}

void WindowManager::newWindow(Renderer *renderer)
{
	static int x = 0;
	static int y = 0;
	static int teller = 0;
	++teller;
	x += 10;
	y += 10;

	DirectXWindow *window = new DirectXWindow(renderer);
	HWND hwnd = window->Create(x, y, 512, 256, NULL, NULL, NULL);

	

	if (hwnd == NULL)
	{
		Logger::getInstance().log(CRITICAL, "Could not make window!");
		return;
	}
	else 
	{
		Logger::getInstance().log(INFO, "Could make window! :)");
	}

	if (renderer->g_pD3D == NULL)
	{
		renderer->Renderer::Initialize(hwnd);
	};

	Logger::getInstance().log(CRITICAL, "Hey! :)");

	WindowList *list = new WindowList();
	list->window = window;
	list->next = windows;
	windows = list;
}


void WindowManager::updateWindows()
{
	MSG Msg;
	while (PeekMessage(&Msg, NULL, 0U, 0U, true) > 0)//mochten er meerdere messages beschikbaar zijn, handel ze allemaal af
	{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
	}
}

bool WindowManager::hasActiveWindow()
{
	//Logger::getInstance().log(INFO, "Er zijn nog windows!");
	WindowList *previous = NULL;
	WindowList *current = windows;
	while (current != NULL)
	{
		if (current->window->state == closed)
		{
			if (current == windows)//het is de huidige root
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
	
	Logger::getInstance().log(CRITICAL, "Er zijn geen windows!");
	return false;
}