#include "Particle.h"


Particle::Particle() {

	texture = new Texture(L"box1");

	vs = new VertexShader(L"VS_PUV", VT_PU);
	ps = new PixelShader(L"PS_PUV");

	position = { 0.0f, 0.0f, 0.0f };

	RectF dim;
	dim.l = 0.0f;
	dim.t = 1.0f;
	dim.r = 1.0f;
	dim.b = 0.0f;

	collision.x = 0.0f;
	collision.y = 1.0f;
	collision.z = 1.0f;
	collision.w = 0.0f;

	float zd = 0.0f;

	VertexPU verts[] = {


		{	XMFLOAT3(dim.l, dim.t, zd),		XMFLOAT2(0.0f,0.0f)		},
		{	XMFLOAT3(dim.r, dim.t, zd),		XMFLOAT2(1.0f,0.0f)		},
		{	XMFLOAT3(dim.l, dim.b, zd),		XMFLOAT2(0.0f,1.0f)		},
		{	XMFLOAT3(dim.r, dim.b, zd),		XMFLOAT2(1.0f,1.0f)		}


	};  
	numElements = ARRAYSIZE(verts);


	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VertexPU) * numElements;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = verts;
	device->CreateBuffer(&bd, &InitData, &vertexBuffer);



}

void Particle::SetResources() {

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	UINT stride = sizeof(VertexPU);
	UINT offset = 0;

	context->VSSetShader(vs->vertexShader.Get(), 0, 0);
	context->VSSetConstantBuffers(0, 1, constantBuffer_finalMatrix.GetAddressOf());
	context->PSSetShader(ps->pixelShader.Get(), 0, 0);

	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	context->IASetInputLayout(vs->inputLayout.Get());
	context->PSSetShaderResources(0, 1, texture->textureResource.GetAddressOf());



}

void Particle::Update() {



	//position.x += 0.002f;
	//position.y += 0.002f;
	//XMMATRIX matRotate = XMMatrixRotationY(0.0f) * XMMatrixTranslation(position.x, position.y, position.z);

	//XMStoreFloat4x4(&world, matRotate);


}

void Particle::Draw(float x, float y, float z) {

	SetResources();

	XMMATRIX fMat = XMMatrixTranslation(x, y, z) * camera->GetCameraScreenMatrix();
	//XMMATRIX fMat = XMLoadFloat4x4(&world) * cameraScreenMatrix;
	VS_C_BUFFER cb;
	XMStoreFloat4x4(&cb.wvp, fMat);

	context->UpdateSubresource(constantBuffer_finalMatrix.Get(), 0, 0, &cb, 0, 0);

	context->Draw(numElements, 0);


}