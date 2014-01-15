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

Resource* ResourceManager::getResource(char *path)
{
	std::stringstream sstm;
	sstm << path;

	if (ResourceMap.find(path) == ResourceMap.end()){

		if (sstm.str().substr(sstm.str().find_last_of(".") + 1) == "bmp" || sstm.str().substr(sstm.str().find_last_of(".") + 1) == "BMP") {
			Resource *bmprsrc = new BMPresource(path);
			if (bmprsrc->isLoaded){
				ResourceMap.insert(std::make_pair(path, bmprsrc));
			}
			else
			{
				std::stringstream sstm;
				sstm << "BMP resource is NULL";
				Logger::getInstance().log(INFO, sstm.str());
			}
		}
		if (sstm.str().substr(sstm.str().find_last_of(".") + 1) == "x" || sstm.str().substr(sstm.str().find_last_of(".") + 1) == "X") {
			Resource *xrsrc = new XResource(path, g_pd3dDevice, this);
			if (xrsrc->isLoaded){
				ResourceMap.insert(std::make_pair(path, xrsrc));
				Logger::getInstance().log(INFO, "Ik heb een X in de map gezet!");
			}
			else
			{
				std::stringstream sstm;
				sstm << "X resource is NULL";
				Logger::getInstance().log(INFO, sstm.str());
			}

		}
	}
	else
	{
		Logger::getInstance().log(INFO, "Ik heb een resource gereturned!");
		return ResourceMap[path];
	}
}

TextureResource* ResourceManager::getTexture(char *path)
{
	std::stringstream sstm;
	sstm << path;

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
				std::stringstream sstm;
				sstm << "Texture resource is NULL";
				Logger::getInstance().log(INFO, sstm.str());
			}
		}
	
	else
	{
		Logger::getInstance().log(INFO, "Ik heb een resource gereturned!");
		return (TextureResource*)ResourceMap[path];
	}
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

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

