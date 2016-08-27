#include "RectData.h"

RectData::RectData(float l, float t, float r, float b) {

	vs = new VertexShader(L"VS_BasicMatrix");
	ps = new PixelShader(L"PS_Basic");

	left =l;
	top = t;
	right = r;
	bottom = b;

	draw_X = 0.0f;
	draw_Y = 0.0f;

	position = { 0.0f, 0.0f, 0.0f };

	w = r-l;
	h = t-b;

	origin_X = w/2;
	origin_Y = h/2;

	float zf = 0.0f;

	VertexP verts[] = {

		XMFLOAT3(l, t, zf),
		XMFLOAT3(r, t, zf),

		XMFLOAT3(r, b, zf),
		XMFLOAT3(l, b, zf),
		XMFLOAT3(t, l, zf)


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


void RectData::Update() {


	//position.x += 0.1;
	//position.y += 0.1;
	//position.z += 0.1;

}
void RectData::Draw() {

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	UINT stride = sizeof(VertexP);
	UINT offset = 0;


	context->VSSetShader(vs->vertexShader.Get(), 0, 0);
	context->PSSetShader(ps->pixelShader.Get(), 0, 0);

	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	context->IASetInputLayout(vs->inputLayout.Get());


	//XMMATRIX fm = (XMMatrixIdentity() * XMMatrixTranslation(position.x, position.y, position.z)) * cameraScreenMatrix;
	XMMATRIX fm =  XMMatrixTranslation(position.x, position.y, position.z) * cameraScreenMatrix;

	

	ConstantBuffer cb;
	cb.finalMatrix = fm;
	cb.screen = fm;
	cb.world = fm;




	context->UpdateSubresource(constantBuffer.Get(), 0, 0, &cb, 0, 0);






	context->Draw(numElements, 0);
}