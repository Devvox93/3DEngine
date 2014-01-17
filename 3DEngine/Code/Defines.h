#ifndef _DEFINES_H_
#define _DEFINES_H_

//A header file to use for cross-class definition of stuff.
#define PI 3.14159265f
#define SPEED 0.3f

struct Vertex
{
	float x,
	y,
	z,
	u,//texture coordinate x
	v;//texture coordinate y
};

#endif