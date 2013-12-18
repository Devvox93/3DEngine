#include "Resource.h"

typedef unsigned char BYTE;

struct Heightmap
{
	int width;
	int height;
	BYTE* pixelData;
};

class HeightmapResource : public Resource
{
public:
	HeightmapResource(char* path);
	~HeightmapResource();
	Heightmap* data;
private:
};

