/*
3D Engine
Xresource.h
Purpose: Loads X resources.

@author Patrick, Nick, Robert, Jordi
@version 1.0
*/

#ifndef _RESOURCE_H_
#define _RESOURCE_H_

class Resource
{
public:
	Resource(char *path);
	Resource();
	~Resource();
	bool isLoaded;
};
#endif