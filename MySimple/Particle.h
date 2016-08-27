#pragma once
#include "Headers.h"
#include "Shader.h"
#include "Texture.h"

extern ComPtr<ID3D11Buffer> constantBuffer_finalMatrix;
extern XMMATRIX cameraMatrix;
extern XMMATRIX screenMatrix;
extern XMMATRIX cameraScreenMatrix;

class Particle {

public:

	Particle();
	void SetResources();
	void Draw();
	void Update();

	XMFLOAT3 OriginPos;
	XMFLOAT3 DrawPos;
	XMFLOAT4 collision;

	UINT numElements;

	ComPtr<ID3D11Buffer>		vertexBuffer;

	XMFLOAT4X4 world;
	XMFLOAT3 position;

	PixelShader* ps;
	VertexShader* vs;
	Texture* texture;
};