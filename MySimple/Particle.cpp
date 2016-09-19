#include "Particle.h"


Particle::Particle() {

	texture = dat.GetTexture(D_TEX_BOX1);

	vs = dat.GetVertexShader(D_VS_PUV);
	ps = dat.GetPixelShader(D_PS_PUV);


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
	context->VSSetConstantBuffers(0, 1, cbPerMesh.GetAddressOf());
	context->PSSetShader(ps->pixelShader.Get(), 0, 0);

	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	context->IASetInputLayout(vs->inputLayout.Get());
	context->PSSetShaderResources(0, 1, texture->textureResource.GetAddressOf());

	PS_C_BUFFER aatemp = { XMFLOAT2{ 0.0f, 0.0f } };

	//context->UpdateSubresource(cbScreen.Get(), 0, 0, &aatemp, 0, 0);



}

void Particle::Update() {





}

void Particle::Draw(float x, float y, float z) {

	SetResources();

	XMMATRIX fMat = XMMatrixTranslation(x, y, z) * camera->GetCameraScreenMatrix();
	//XMMATRIX fMat = XMLoadFloat4x4(&world) * cameraScreenMatrix;
	VS_C_BUFFER cb;
	XMStoreFloat4x4(&cb.wvp, fMat);

	context->UpdateSubresource(cbPerMesh.Get(), 0, 0, &cb, 0, 0);

	context->Draw(numElements, 0);


}