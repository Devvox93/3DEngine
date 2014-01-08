typedef unsigned char BYTE;

struct GroundData
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

class Ground
{
public:
	Ground(char* path);
	~Ground();
	GroundData* data;
	Vertex* aGroundVertices;
	int amountOfIndices;
	int* aGroundIndices;
private:
};

