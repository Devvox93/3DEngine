typedef unsigned char BYTE;

struct TerrainData
{
	int width;
	int height;
};

struct Vertex
{
	float x,
	y,
	z,
	u,//texture coordinate x
	v;//texture coordinate y
};

class Terrain
{
public:
	Terrain(char* path);
	~Terrain();
	TerrainData* data;
	Vertex* aTerrainVertices;
	int amountOfIndices;
	int* aTerrainIndices;
private:
};

