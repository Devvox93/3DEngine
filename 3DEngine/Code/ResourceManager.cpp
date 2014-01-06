#include "ResourceManager.h"
#include "Resource.h"
#include "Logger.h"
#include <map>
#include "windows.h"
#include <sstream>
  
std::map<char*, Resource> ResourceMap;


void ResourceManager::storeResource(char *path)
{
	if (ResourceMap.find(path) == ResourceMap.end()){
		Resource *hmprsrc = new Resource(path);
		ResourceMap.insert(std::make_pair(path, *hmprsrc));
	}
	else
	{
		std::stringstream sstm;
		sstm << "Already exist in the map!!";
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

