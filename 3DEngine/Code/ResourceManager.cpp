#include "ResourceManager.h"
#include "Resource.h"
#include "BMPresource.h"
#include "XResource.h"
#include "Logger.h"
#include <map>
#include "windows.h"
#include <iostream>
#include <sstream>
#include <string.h>
#include <string>
  
std::map<char*, Resource*> ResourceMap;


void ResourceManager::storeResource(char *path)
{
	std::stringstream sstm;
	sstm << "Path = " << path;
	
	if (ResourceMap.find(path) == ResourceMap.end()){

		if (sstm.str().substr(sstm.str().find_last_of(".") + 1) == "bmp"&&"BMP") {
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
		if (sstm.str().substr(sstm.str().find_last_of(".") + 1) == "x"&&"X") {
			Resource *xrsrc = new XResource(path);
			if (xrsrc->isLoaded){
				ResourceMap.insert(std::make_pair(path, xrsrc));
			}
			else
			{				
				std::stringstream sstm;
				sstm << "X resource is NULL";
				Logger::getInstance().log(INFO, sstm.str());
			}

		}
	}
	}

void ResourceManager::PrintMap()
{
	for (std::map<char*, Resource*>::const_iterator it = ResourceMap.begin(); it != ResourceMap.end(); it++)
	{
		std::stringstream sstm;
		char* key = it->first;
		sstm << "Saved in Map = " << key;
		Logger::getInstance().log(INFO, sstm.str());
	}
}

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

