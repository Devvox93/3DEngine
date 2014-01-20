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