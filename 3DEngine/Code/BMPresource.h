/*
	3D Engine
	BMPresource.h
	Purpose: Loads BMP resources.

	@author Patrick, Nick, Robert, Jordi
	@version 1.0
*/

#ifndef _BMPRESOURCE_H_
#define _BMPRESOURCE_H_

#include "Resource.h"
#include <string>

class BMPresource : public Resource
{
public:
	/*
		Loads a BMP resource from file.

		@param path: Path to the .bmp-file
	*/
	BMPresource(std::string path);

	~BMPresource();
};
#endif
