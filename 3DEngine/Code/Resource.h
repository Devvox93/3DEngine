/*
	3D Engine
	Resource.h
	Purpose: Class to keep track which resources are loaded.

	@author Patrick, Nick, Robert, Jordi
	@version 1.0
*/

#ifndef _RESOURCE_H_
#define _RESOURCE_H_

class Resource
{
public:
	/*
		Creates a resource and loads the resource file.

		@param path: The path to the resource file on disk.
	*/
	Resource(char *path);
	Resource();
	~Resource();
	bool isLoaded;
};
#endif