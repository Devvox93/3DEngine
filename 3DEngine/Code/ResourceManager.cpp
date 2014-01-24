#include "ResourceManager.h"
#include "Resource.h"
#include "BMPresource.h"
#include "XResource.h"
#include "Logger.h"
#include "windows.h"
#include <iostream>
#include <sstream>
#include <string.h>
#include <string>

ResourceManager::ResourceManager()
{
};

ResourceManager::~ResourceManager()
{
	
	ResourceMap.clear();
	delete bmprsrc;
	delete xrsrc;
	delete txrsrc;
	if (g_pd3dDevice != NULL)
	{
		g_pd3dDevice = NULL;
	}


};

Resource* ResourceManager::getResource(std::string path)
{
	if (ResourceMap.find(path) == ResourceMap.end())
	{
		if (path.substr(path.find_last_of(".") + 1) == "bmp" || path.substr(path.find_last_of(".") + 1) == "BMP")
		{
			Resource *bmprsrc = new BMPresource(path);
			if (bmprsrc->isLoaded){
				ResourceMap.insert(std::make_pair(path, bmprsrc));
				return ResourceMap[path];
			}
			else
			{
				Logger::getInstance().log(INFO, "Could not load BMP: " + path);
			}
		}
		if (path.substr(path.find_last_of(".") + 1) == "x" || path.substr(path.find_last_of(".") + 1) == "X")
		{
			xrsrc = new XResource(path, g_pd3dDevice, this);
			if (xrsrc->isLoaded)
			{
				ResourceMap.insert(std::make_pair(path, xrsrc));
				return ResourceMap[path];
			}
			else
			{
				Logger::getInstance().log(INFO, "Could not load X: " + path);
			}
		}
		return NULL;
	}
	else
	{
		return ResourceMap[path];
	}
};

TextureResource* ResourceManager::getTexture(std::string path)
{
	if (ResourceMap.find(path) == ResourceMap.end())
	{
		txrsrc = new TextureResource(path, g_pd3dDevice);
		if (txrsrc->isLoaded)
		{
			ResourceMap.insert(std::make_pair(path, txrsrc));
			return (TextureResource*)ResourceMap[path];
		}
		else
		{
			Logger::getInstance().log(INFO, "Could not load texture: " + path);
		}
	}
	else
	{
		return (TextureResource*)ResourceMap[path];
	}
	return NULL;
};

void ResourceManager::PrintMap()
{
	for (std::map<std::string, Resource*>::const_iterator it = ResourceMap.begin(); it != ResourceMap.end(); it++)
	{
		std::stringstream sstm;
		sstm << "Saved in Map = " << it->first;;
		Logger::getInstance().log(INFO, sstm.str());
	}
};

std::vector<std::string>* ResourceManager::getSceneFile(std::string path)
{
	std::ifstream file(path);
	std::string line;
	std::vector<std::string>* sceneFile = new std::vector<std::string>();
	if (file)
	{
		while (std::getline(file, line))
		{
			sceneFile->push_back(line);
		}
	}
	else 
	{
		Logger::getInstance().log(INFO, "Scene was not found, using HELLO WORLD instead");
		std::ifstream file("default.txt");
		while (std::getline(file, line))
		{
			sceneFile->push_back(line);
		}
	}
	return sceneFile;
};

void ResourceManager::setD3DDevice(LPDIRECT3DDEVICE9 device)
{
	g_pd3dDevice = device;
}