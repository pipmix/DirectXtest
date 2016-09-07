#include "Shape.h"

ShapeRectangle::ShapeRectangle() :_depth(0.0f){

}

void ShapeRectangle::Create(float left, float top, float right, float bottom){


	_left = left;
	_top = top;
	_right = right;
	_bottom = bottom;
	_Init = true;
	

	LPCWSTR filenameVS = L"C:/Shaders/VS_BasicMatrix.cso";
	LPCWSTR filenamePS = L"C:/Shaders/PS_Basic.cso";

	UINT8*	vsData;
	UINT	vsDataLength;

	UINT8*	psData;
	UINT	psDataLength;

	ReadDataFromFile(filenameVS, &vsData, &vsDataLength);
	ReadDataFromFile(filenamePS, &psData, &psDataLength);

	device->CreateVertexShader(vsData, vsDataLength, nullptr, &_vertexShader);
	device->CreatePixelShader(psData, psDataLength, nullptr, &_pixelShader);




	VertexP verts[] = {

		XMFLOAT3(left,top,_depth),
		XMFLOAT3(right,top,_depth),

		XMFLOAT3(right,bottom,_depth),
		XMFLOAT3(left,bottom,_depth),
		XMFLOAT3(left,top,_depth)


	}; _numElements = ARRAYSIZE(verts);






	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VertexP) * _numElements;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = verts;
	device->CreateBuffer(&bd, &InitData, &_vertexBuffer);



	device->CreateInputLayout(VertexP_Layout, ARRAYSIZE(VertexP_Layout), vsData, vsDataLength, &_inputLayout);


}

void ShapeRectangle::SetDepth(float z)
{
	_depth = z;
}

void Shape::Draw(){

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	UINT stride = sizeof(VertexP);
	UINT offset = 0;

	context->VSSetShader(_vertexShader.Get(), 0, 0);
	context->VSSetConstantBuffers(0, 1, constantBuffer_finalMatrix.GetAddressOf());
	context->PSSetShader(_pixelShader.Get(), 0, 0);
	context->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset);
	context->IASetInputLayout(_inputLayout.Get());

	XMMATRIX fMat = XMMatrixTranslation(0, 0, 0) * camera->GetCameraScreenMatrix();
	VS_C_BUFFER cb;
	XMStoreFloat4x4(&cb.wvp, fMat);
	context->UpdateSubresource(constantBuffer_finalMatrix.Get(), 0, 0, &cb, 0, 0);
	context->Draw(_numElements, 0);


}

void Shape::Update() {


}

ShapeCircle::ShapeCircle()
{
}

ShapeLine::ShapeLine()
{
}
