#pragma once
#include "Headers.h"


enum VertexType {

	VT_P, VT_PU, VT_PNU
};

struct VS_C_BUFFER
{
	XMFLOAT4X4 wvp;


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

#define TEX_ELEMENTS 3
#define TEX_DIFFUSE 0
#define TEX_SPECULAR 1
#define TEX_NORMAL 2

#define TEX_BRICK 0
#define TEX_TILE 1
