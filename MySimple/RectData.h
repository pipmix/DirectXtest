#pragma once
#include "DataTypes.h"
#include "Shader.h"

extern ComPtr<ID3D11Device>			device;
extern ComPtr<ID3D11DeviceContext>	context;



extern bool LL;
extern bool RR;
extern bool UU;

class RectData {

public:


	RectData(float l, float t, float r, float b);


	ComPtr<ID3D11Buffer>		vertexBuffer;

	float left;
	float top;
	float right;
	float bottom;

	float draw_X;
	float draw_Y;

	float origin_X;
	float origin_Y;

	float w;
	float h;

	UINT numElements;
	

	PixelShader* ps;
	VertexShader* vs;

	void Update();
	void Draw();

	XMFLOAT3 position;
	XMFLOAT4X4 world;
};