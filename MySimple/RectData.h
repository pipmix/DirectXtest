#pragma once
#include "DataTypes.h"
#include "Shader.h"
#include "Camera.h"

extern ComPtr<ID3D11Device>			device;
extern ComPtr<ID3D11DeviceContext>	context;


extern ComPtr<ID3D11Buffer> constantBuffer_finalMatrix;
extern Camera* camera;

class RectData {

public:


	RectData(float posX, float posY, float w, float h);

	void SetDim(float left, float top, float right, float bottom);
	//void SetDim(RectF floatRect);
	void SetPosition(float x, float y, float z);
	void SetWH();
	void SetRect(float x, float y, float w, float h);


	ComPtr<ID3D11Buffer>		vertexBuffer;

	RectF _data;

	float _left;
	float _top;
	float _right;
	float _bottom;

	float _draw_X;
	float _draw_Y;

	float origin_X;
	float origin_Y;

	float _width;
	float _height;

	UINT numElements;
	

	PixelShader* ps;
	VertexShader* vs;

	void Update();
	void Draw();

	XMFLOAT3 position;
	XMFLOAT4X4 world;
};