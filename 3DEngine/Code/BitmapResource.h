#include "Resource.h"
class BitmapResource : public Resource
{
public:
	BitmapResource(char* path);
	~BitmapResource();
	BYTE* pixelData;
};

