#pragma once
#include "Headers.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Data.h"

extern ComPtr<ID3D11Buffer> cbPerMesh;
extern Data* dat;

extern Camera* camera;

class Particle {

public:

	Particle();
	void SetResources();
	void Draw(float x, float y, float z);
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

