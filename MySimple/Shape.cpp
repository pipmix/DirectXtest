#include "Shape.h"

ShapeRectangle::ShapeRectangle() :_depth(0.0f){

}

void ShapeRectangle::Create(float left, float top, float right, float bottom){


	_left = left;
	_top = top;
	_right = right;
	_bottom = bottom;
	_Init = true;
	
	vs = dat->GetVertexShader(D_VS_BASICMATRIX);
	ps = dat->GetPixelShader(D_PS_BASIC);






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


	_collision = { left, top, right, bottom };
}

void ShapeRectangle::SetDepth(float z)
{
	_depth = z;
}

XMFLOAT4 ShapeRectangle::GetCollision()
{
	return _collision;
}

void Shape::Draw(){

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	UINT stride = sizeof(VertexP);
	UINT offset = 0;

	context->VSSetShader(vs->vertexShader.Get(), 0, 0);
	context->VSSetConstantBuffers(0, 1, constantBuffer_finalMatrix.GetAddressOf());
	context->PSSetShader(ps->pixelShader.Get(), 0, 0);
	context->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset);
	context->IASetInputLayout(vs->inputLayout.Get());

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

ShapePoint::ShapePoint()
{
}

void ShapePoint::Create(float x, float y, float z)
{
}

LineShape3d::LineShape3d()
{
}

void LineShape3d::Create(){

	vs = dat->GetVertexShader(D_VS_BASICMATRIX);
	ps = dat->GetPixelShader(D_PS_BASIC);


	float offset = 5.0f;
	float origin = 0.0f;


	VertexP* verts;
	
	XMFLOAT2 points[] = {
		{ 0.0f,	0.0f },
		{ 1.0f,	1.0f },
		{ 2.0f,	1.0f },
		{ 2.0f,	0.0f },
		{ 1.0f,	0.0f },
	}; int numPoints = ARRAYSIZE(points);

	verts = new VertexP[numPoints * 3 * 2];

	XMFLOAT2 point1;
	XMFLOAT2 point2;

	for (int i = 0; i < numPoints; i++) {

		point1 = points[i];
		if (i == (numPoints - 1)) point2 = points[0];
		else point2 = points[i + 1];


		verts[i * 6 + 0] = VertexP{ point1.x, point1.y, origin };
		verts[i * 6 + 1] = VertexP{ point2.x, point2.y, origin };
		verts[i * 6 + 2] = VertexP{ point2.x, point2.y, offset };

		verts[i * 6 + 3] = VertexP{ point1.x, point1.y, origin };
		verts[i * 6 + 4] = VertexP{ point2.x, point2.y, offset };
		verts[i * 6 + 5] = VertexP{ point1.x, point1.y, offset };

	};
	
	_numElements = numPoints * 3 * 2;



	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VertexP) * _numElements;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = verts;
	device->CreateBuffer(&bd, &InitData, &_vertexBuffer);

}

void LineShape3d::Draw() {
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = sizeof(VertexP);
	UINT offset = 0;

	context->VSSetShader(vs->vertexShader.Get(), 0, 0);
	context->VSSetConstantBuffers(0, 1, constantBuffer_finalMatrix.GetAddressOf());
	context->PSSetShader(ps->pixelShader.Get(), 0, 0);
	context->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset);
	context->IASetInputLayout(vs->inputLayout.Get());

	XMMATRIX fMat = XMMatrixTranslation(0, 0, 0) * camera->GetCameraScreenMatrix();
	VS_C_BUFFER cb;
	XMStoreFloat4x4(&cb.wvp, fMat);
	context->UpdateSubresource(constantBuffer_finalMatrix.Get(), 0, 0, &cb, 0, 0);
	context->Draw(_numElements, 0);



}
