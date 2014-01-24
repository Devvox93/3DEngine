/*
	3D Engine
	Defines.h
	Purpose: Global defines used in the Engine.

	@author Patrick, Nick, Robert, Jordi
	@version 1.0
*/

//A header file to use for cross-class definition of stuff.
#ifndef _DEFINES_H_
#define _DEFINES_H_

#define DIRECTINPUT_VERSION 0x0800
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_TEX1)
#define M_PI 3.14159265358979323846f
#define RADIANS(degree) (M_PI * (degree) / 180.0f)
#define DEGREES(radian) (radian) * (180 / M_PI)
#define SPEED 0.5f

typedef unsigned char BYTE;

struct Vertex
{
	float x,
	y,
	z,
	u,//texture coordinate x
	v;//texture coordinate y
};

struct TripleFloat
{
	float x, y, z;
};
#endif