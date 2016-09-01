#include "TileBatch.h"


TileBatch::TileBatch() {


}

void TileBatch::LoadMap(){

	texture = new Texture(L"set");
	vs = new VertexShader(L"VS_PUV", VT_PU);
	ps = new PixelShader(L"PS_PUV");

	int mapArr[] = {

		0,2,3,4,1,1,2,2,
		2,1,1,1,1,1,2,2,
		2,1,1,1,1,1,2,2,
		2,1,3,1,1,1,2,2,
		2,2,1,1,1,1,1,2,
		2,2,1,1,1,1,1,2,
		2,2,1,1,1,1,1,2,
		2,2,1,3,1,1,2,2,
	};

	texNoCol = 7;
	texNoRow = 6;

	float cPiece = 0.2f;//1.0f / (float)texNoCol;
	float rPiece = 0.2f;//1.0f / (float)texNoRow;

	noColumns = 8;
	noRows = 8;

	arrSize = noColumns*noRows;
	numElements = arrSize * 6;

	VertexPU* verts;
	
	verts = new VertexPU[numElements];

	int l, t, r, b, zz;
	int uvL, uvR, uvT, uvB;
	int s = 0;
	int sizeScale = 1;

	//curCol = 0; curRow = 0;
	for (int i = 0; i < arrSize; i++) {

		s = i * 6;

		//RectI rectI = GetRect(curCol, curRow);

		int tLocX = (mapArr[i] % noColumns) - 1; // 2
		int tLocY = (mapArr[i] / noColumns); //12

		int sz = 1;
		l = curCol * sz;
		t = (-curRow) * sz;
		r = l + sz;
		b = t - sz;
		zz = 0;

		uvL = 0.2;//tLocX * cPiece;
		uvT = 0.2;//tLocY * rPiece;;
		uvR = 1.0f;//uvL + cPiece;
		uvB = 1.0f;//tLocY + rPiece;



		verts[s] = { XMFLOAT3(l, t, zz), XMFLOAT2(uvL, uvT) };
		verts[s+1] = { XMFLOAT3(r, t, zz), XMFLOAT2(uvR, uvT) };
		verts[s+2] = { XMFLOAT3(l, b, 0), XMFLOAT2(uvL, uvB) };

		verts[s+3] = { XMFLOAT3(l, b , zz), XMFLOAT2(uvL, uvB) };
		verts[s+4] = { XMFLOAT3(r, t, zz), XMFLOAT2(uvR, uvT) };
		verts[s+5] = { XMFLOAT3(r, b, zz), XMFLOAT2(uvR, uvB) };

		if (curCol < noColumns - 1) curCol++;
		else {
			curCol = 0;
			curRow++;
		}

		//sourceRect.left = (tLocX * texTileW);
		//sourceRect.top = (tLocY * texTileH);
		//sourceRect.right = sourceRect.left + texTileW;
		//sourceRect.bottom = sourceRect.top + texTileH;



	}
	//int noColumns = 0, noRows = 0, arrSize = 0, tileW = 0, tileH = 0, currentRow = 0;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VertexPU) * numElements;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = verts;
	device->CreateBuffer(&bd, &InitData, &vBuffer);



}

void TileBatch::SetResources(){
	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	UINT stride = sizeof(VertexPU);
	UINT offset = 0;

	context->VSSetShader(vs->vertexShader.Get(), 0, 0);
	context->VSSetConstantBuffers(0, 1, constantBuffer_finalMatrix.GetAddressOf());
	context->PSSetShader(ps->pixelShader.Get(), 0, 0);

	context->IASetVertexBuffers(0, 1, vBuffer.GetAddressOf(), &stride, &offset);
	context->IASetInputLayout(vs->inputLayout.Get());
	context->PSSetShaderResources(0, 1, texture->textureResource.GetAddressOf());



}




void TileBatch::Draw() {

	SetResources();
	x = 0;
	y = 0;
	x = 0;

	XMMATRIX fMat = XMMatrixTranslation(x, y, z) * cameraScreenMatrix;
	//XMMATRIX fMat = XMLoadFloat4x4(&world) * cameraScreenMatrix;
	VS_C_BUFFER cb;
	XMStoreFloat4x4(&cb.wvp, fMat);

	context->UpdateSubresource(constantBuffer_finalMatrix.Get(), 0, 0, &cb, 0, 0);

	context->Draw(numElements, 0);


}