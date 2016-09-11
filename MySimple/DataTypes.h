#pragma once
#include "Headers.h"

struct Box {
	float x;
	float y;
	float w;
	float h;
};

struct Point {
	float x;
	float y;
	float z;
};

struct Line {
	Point A;
	Point B;
};



enum VertexType {

	VT_P, VT_PU, VT_PNU
};

struct VS_C_BUFFER
{
	XMFLOAT4X4 wvp;


};

struct PS_C_BUFFER {
	XMFLOAT2 scr;
};

struct RectF {
	float l;
	float t;
	float r;
	float b;

	RectF() {
		l = t = r = b = 0.0f;
	}

	RectF(float left, float top, float right, float bottom) {
		l = left;
		t = top;
		r = right;
		b = bottom;

	}

	void SetPWH(float x, float y, float w, float h) {
		l = x;
		t = y;
		r = l + w;
		b = t - h;

	};
};

struct RectI {
	int l;
	int t;
	int r;
	int b;

	void SetPWH(int x, int y, int w, int h) {
		l = x;
		t = y;
		r = l + w;
		b = t - h;

	};
};

struct VertexP {
	XMFLOAT3 position;
	VertexP() {};
	VertexP(XMFLOAT3 p) : position(p) {};
	VertexP(float x, float y, float z) {
		position.x = x;
		position.y = y;
		position.z = z;
	};
};


static const D3D11_INPUT_ELEMENT_DESC VertexP_Layout[] ={
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

struct VertexPU {
	XMFLOAT3 position;
	XMFLOAT2 uvcoord;
};


static const D3D11_INPUT_ELEMENT_DESC VertexPU_Layout[] = {

	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }

};

struct VERTEXPNU {
	XMFLOAT3 pos;
	XMFLOAT3 normal;
	XMFLOAT2 uv;
};

const D3D11_INPUT_ELEMENT_DESC layoutPNU[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

#define D_TEX_ELEMENTS 3
#define D_TEX_DIFFUSE 0
#define D_TEX_SPECULAR 1
#define D_TEX_NORMAL 2

#define D_TEX_BRICK 0
#define D_TEX_BOX1 1
#define D_TEX_SET 2

#define D_VS_PUV 0
#define D_VS_BASIC 1
#define D_VS_BASICMATRIX 2

#define D_PS_PUV 0
#define D_PS_BASIC 1


struct ItemData {

	const char* itemName;
	float value;
	float weight;

} static const ItemTypes[] = {

	{	"Gold",		10.0f,		10.0f	},
	{	"Silver",	5.0f,		10.0f	},
	{	"Bronze",	1.0f,		10.0f },
},
WeaponTypes[] = {

	{ "Sword",		100.0f,		21.0f },
	{ "Axe",		50.0f,		10.0f },
	{ "Gun",		12.0f,		10.0f },
};


class GameObj {

public:

	XMFLOAT3	GetPosition		()							{ return _position; }
	XMFLOAT3	GetVelocity		()							{ return _velocity; }
	Box			GetCollision	()							{ return _collision; }

	void		SetPosition		(XMFLOAT3 newPosition)			{ _position = newPosition; }
	void		SetVelocity		(XMFLOAT3 newVelocity)			{ _velocity = newVelocity; }
	void		SetCollision	(Box newCollision)				{ _collision = newCollision; }

protected:

	XMFLOAT3	_position;
	XMFLOAT3	_velocity;
	Box			_collision;


};

class Anim2d {
public:
	char* name;
	int numFrames;
	int* frames;


};

