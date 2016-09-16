#include "RectData.h"

RectData::RectData(float posX, float posY, float w, float h) {

	vs = new VertexShader(L"VS_BasicMatrix", VT_P);
	ps = new PixelShader(L"PS_Basic");

	_data.l = posX;
	_data.t = posY;
	_data.r = posX + w;
	_data.b = posY - h;

	//left =l;
	//top = t;
	//right = r;
	//bottom = b;

	_draw_X = posX;
	_draw_Y = posY;

	position = { 0.0f, 0.0f, 0.0f };

	origin_X = w/2;
	origin_Y = h/2;

	float zf = 0.0f;
	float zd = 0.5f;

	VertexP verts[] = {

		XMFLOAT3(_data.l, _data.t, zf),
		XMFLOAT3(_data.r, _data.t, zf),
		XMFLOAT3(_data.l, _data.b, zf),

		XMFLOAT3(_data.r, _data.t, zf),
		XMFLOAT3(_data.r, _data.b, zf),
		XMFLOAT3(_data.l, _data.b, zf),


		XMFLOAT3(_data.l, _data.t, zd),
		XMFLOAT3(_data.r, _data.t, zd),
		XMFLOAT3(_data.l, _data.b, zd),

		XMFLOAT3(_data.r, _data.t, zd),
		XMFLOAT3(_data.r, _data.b, zd),
		XMFLOAT3(_data.l, _data.b, zd),


	}; numElements = ARRAYSIZE(verts);



	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VertexP) * numElements;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = verts;
	device->CreateBuffer(&bd, &InitData, &vertexBuffer);

	


}


void RectData::SetDim(float left, float top, float right, float bottom)
{
}

void RectData::SetPosition(float x, float y, float z)
{
}

void RectData::SetWH()
{
}

void RectData::SetRect(float x, float y, float w, float h)
{
}

void RectData::Update() {

	position.x += 0.002f;
	position.y += 0.002f;
	XMMATRIX matRotate = XMMatrixRotationY(0.0f) * XMMatrixTranslation(position.x, position.y, position.z);

	XMStoreFloat4x4(&world, matRotate);


}
void RectData::Draw() {

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = sizeof(VertexP);
	UINT offset = 0;


	context->VSSetShader(vs->vertexShader.Get(), 0, 0);
	context->VSSetConstantBuffers(0, 1, cbPerMesh.GetAddressOf());
	context->PSSetShader(ps->pixelShader.Get(), 0, 0);
	

	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	context->IASetInputLayout(vs->inputLayout.Get());


	XMMATRIX fMat = XMLoadFloat4x4(&world) * camera->GetCameraScreenMatrix();
	VS_C_BUFFER cb;
	XMStoreFloat4x4(&cb.wvp, fMat);
	
	context->UpdateSubresource(cbPerMesh.Get(), 0, 0, &cb, 0, 0);









	context->Draw(numElements, 0);
}