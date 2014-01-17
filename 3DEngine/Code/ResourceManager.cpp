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

Resource* ResourceManager::getResource(std::string path)
{
	if (ResourceMap.find(path) == ResourceMap.end()){

		if (path.substr(path.find_last_of(".") + 1) == "bmp" || path.substr(path.find_last_of(".") + 1) == "BMP") {
			Resource *bmprsrc = new BMPresource(path);
			if (bmprsrc->isLoaded){
				ResourceMap.insert(std::make_pair(path, bmprsrc));
				return ResourceMap[path];
			}
			else
			{
				std::stringstream sstm;
				sstm << "BMP resource is NULL";
				Logger::getInstance().log(INFO, sstm.str());
			}
		}
		if (path.substr(path.find_last_of(".") + 1) == "x" || path.substr(path.find_last_of(".") + 1) == "X") {
			Resource *xrsrc = new XResource(path, g_pd3dDevice, this);
			if (xrsrc->isLoaded){
				ResourceMap.insert(std::make_pair(path, xrsrc));
				Logger::getInstance().log(INFO, "Ik heb een X in de map gezet!");
				return ResourceMap[path];
			}
			else
			{
				std::stringstream sstm;
				sstm << "X resource is NULL";
				Logger::getInstance().log(INFO, sstm.str());
			}
		}
		return NULL;
	}
	else
	{
		Logger::getInstance().log(INFO, "Ik heb een resource gereturned!");
		return ResourceMap[path];
	}
}

TextureResource* ResourceManager::getTexture(std::string path)
{
	if (ResourceMap.find(path) == ResourceMap.end()){
		TextureResource *xrsrc = new TextureResource(path, g_pd3dDevice);
		if (xrsrc->isLoaded){
			std::string pa = path;
			Logger::getInstance().log(INFO, "Path is "+pa);
			ResourceMap.insert(std::make_pair(pa, xrsrc));
			Logger::getInstance().log(INFO, "Ik heb een texture in de map gezet!");
			return (TextureResource*)ResourceMap[path];
		}
		else
		{
			Logger::getInstance().log(INFO, "Texture resource is NULL");
		}
	}
	else
	{
		Logger::getInstance().log(INFO, "Ik heb een texture resource gereturned!");
		return (TextureResource*)ResourceMap[path];
	}
	return NULL;
}

void ResourceManager::PrintMap()
{
	for (std::map<std::string, Resource*>::const_iterator it = ResourceMap.begin(); it != ResourceMap.end(); it++)
	{
		std::stringstream sstm;
		sstm << "Saved in Map = " << it->first;;
		Logger::getInstance().log(INFO, sstm.str());
	}
}

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

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

