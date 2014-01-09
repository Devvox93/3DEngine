#include "ResourceManager.h"
#include "Resource.h"
#include "Logger.h"
#include <map>
#include "windows.h"
#include <iostream>
#include <sstream>
#include <string.h>
#include <string>
  
std::map<char*, Resource> ResourceMap;


void ResourceManager::storeResource(char *path)
{
	

	std::stringstream sstm;
	sstm << "Path = " << path;
	Logger::getInstance().log(INFO, sstm.str());

	if (sstm.str().substr(sstm.str().find_last_of(".") + 1) == "BMP") {
		// aanmaken BMP-ResourceLoader
		Logger::getInstance().log(INFO, sstm.str());
	}
	if (sstm.str().substr(sstm.str().find_last_of(".") + 1) == "x") {
		// aanmaken X-resourceLoader
		Logger::getInstance().log(INFO, sstm.str());
	}
	if (sstm.str().substr(sstm.str().find_last_of(".") + 1) == "m2") {
		// aanmaken X-resourceLoader
		Logger::getInstance().log(INFO, sstm.str());
	}
	if (sstm.str().substr(sstm.str().find_last_of(".") + 1) == "png") {
		// aanmaken X-resourceLoader
		Logger::getInstance().log(INFO, sstm.str());
	}
	if (sstm.str().substr(sstm.str().find_last_of(".") + 1) == "m") {
		// aanmaken X-resourceLoader
		Logger::getInstance().log(INFO, sstm.str());
	}
	if (sstm.str().substr(sstm.str().find_last_of(".") + 1) == "jpg") {
		// aanmaken X-resourceLoader
		Logger::getInstance().log(INFO, sstm.str());
	}
	Logger::getInstance().log(INFO, sstm.str());
	
	
	
	if (ResourceMap.find(path) == ResourceMap.end()){
		Resource *hmprsrc = new Resource(path);
		ResourceMap.insert(std::make_pair(path, *hmprsrc));
	}
	else
	{
		std::stringstream sstm;
		sstm << "Already exist in the map!!!";
		Logger::getInstance().log(INFO, sstm.str());
	}
}

void ResourceManager::PrintMap()
{
	for (std::map<char*, Resource>::const_iterator it = ResourceMap.begin(); it != ResourceMap.end(); it++)
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

