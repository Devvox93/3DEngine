#ifndef _SKYBOX_H_
#define _SKYBOX_H_

struct SVertex
{
	float x,
	y,
	z,
	u,//texture coordinate x
	v;//texture coordinate y
};

class Skybox
{
public:
	Skybox();
	~Skybox();
	SVertex* aSkyboxVertices;
	int* aSkyboxIndices;
private:
};

#endif