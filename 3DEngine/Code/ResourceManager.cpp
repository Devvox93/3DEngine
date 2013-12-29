#include "ResourceManager.h"
#include "windows.h"
#include "HeightmapResource.h"
#include "logger.h"
#include <sstream>

  
void ResourceManager::storeBMP(char *path)
{
	
	
		Logger::getInstance().log(INFO, "Valid path found! Loading...");
		HeightmapResource *hmprsrc = new HeightmapResource(path);
		if (hmprsrc != NULL)
		{
			std::stringstream sstm;
			sstm << "BMP:" <<path << " loaded!";
			Logger::getInstance().log(INFO, sstm.str());

		}
		else
		{
			std::stringstream sstm;
			sstm << "BMP:" << path << " Couldn't load :(";
			Logger::getInstance().log(INFO, sstm.str());
		}
	
	
}


ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

