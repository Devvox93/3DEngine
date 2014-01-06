#include "ResourceManager.h"
#include "windows.h"
#include "HeightmapResource.h"
#include "logger.h"
#include <sstream>
#include <map>
#include <string>
#include <string.h>


std::map<char*, HeightmapResource> ResourceMap;


void ResourceManager::storeResource(char *path)
{
	if (ResourceMap.find(path) == ResourceMap.end()){
		HeightmapResource *hmprsrc = new HeightmapResource(path);
		ResourceMap.insert(std::make_pair(path, *hmprsrc));
	}
	else
	{
		std::stringstream sstm;
		sstm << "Already exist in the map!";
		Logger::getInstance().log(INFO, sstm.str());
	}	
}

void ResourceManager::PrintMap()
{

	for (std::map<char*, HeightmapResource>::const_iterator it = ResourceMap.begin(); it != ResourceMap.end(); it++)
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

