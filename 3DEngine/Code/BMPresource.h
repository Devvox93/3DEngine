#ifndef _BMPRESOURCE_H_
#define _BMPRESOURCE_H_

#include "Resource.h"
#include <string>

class BMPresource : public Resource
{
public:
	BMPresource(std::string path);
	~BMPresource();
};
#endif
