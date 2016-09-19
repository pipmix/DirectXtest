#include "TileBatch.h"


TileBatch::TileBatch() {


}

void TileBatch::LoadMap(){
	m_textureID = D_TEX_SET;
	m_vsID = D_VS_PUV;
	m_psID = D_PS_PUV;
	m_topoID = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;


	int mapArr[] = {

		0,	1,	2,	3,	4,	5,	6,	6,
		7,	8,	9,	10,	11,	12,	13, 13,
		14,	15,	16,	17,	18,	19,	20, 20,
		21,	22, 23,	24,	25,	26, 27, 27,
		28,	29,	30,	31,	32, 33, 34, 34,
		35, 36, 37, 38, 39, 40, 41, 41,
		2,2,1,1,1,1,1,2,
		2,2,1,3,1,1,2,2,
	};

	texNoCol = 7;
	texNoRow = 6;

	float cPiece = 1.0f / (float)texNoCol;
	float rPiece = 1.0f / (float)texNoRow;

	arrNoColumns = 8;
	arrNoRows = 8;

	arrSize = arrNoColumns*arrNoRows;
	numElements = arrSize * 6;

	VertexPU* verts;
	
	verts = new VertexPU[numElements];

	float l, t, r, b, zz;

	int sZ = 1;
	int s = 0;
	zz = 0.0f;


	RectF sR;
	curCol = 0;
	curRow = 0;
	for (int i = 0; i < arrSize; i++) {
		s = i * 6;


		int tLocX = (mapArr[i] % texNoCol);//-1;
		int tLocY = (mapArr[i] / texNoCol);
		

		sR.l = tLocX * cPiece;
		sR.t = tLocY * rPiece;
		sR.r = sR.l + cPiece;
		sR.b = sR.t + rPiece;

		l = curCol * sZ;
		t = -(curRow) * sZ;
		r = l + sZ;
		b = t - sZ;

		verts[s] = {XMFLOAT3(l, t, zz), XMFLOAT2(sR.l, sR.t) };
		verts[s + 1] = { XMFLOAT3(r, t, zz), XMFLOAT2(sR.r, sR.t) };
		verts[s + 2] = { XMFLOAT3(l, b, 0), XMFLOAT2(sR.l, sR.b) };

		verts[s + 3] = { XMFLOAT3(l, b , zz), XMFLOAT2(sR.l, sR.b) };
		verts[s + 4] = { XMFLOAT3(r, t, zz), XMFLOAT2(sR.r, sR.t) };
		verts[s + 5] = { XMFLOAT3(r, b, zz), XMFLOAT2(sR.r, sR.b) };
		

		if (curCol < arrNoColumns - 1) curCol++;
		else {
			curCol = 0;
			curRow++;
		}

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
	device->CreateBuffer(&bd, &InitData, &m_vertexBuffer);



}

void TileBatch::Create(int * dataArray, int columns, int rows){
	/*
	m_textureID = D_TEX_SET;
	m_vsID = D_VS_PUV;
	m_psID = D_PS_PUV;

	//7 6

	
	texNoCol = dat->GetTexture(m_textureID)->_columns;
	texNoRow = dat->GetTexture(m_textureID)->_rows;

	float cPiece = 1.0f / (float)texNoCol;
	float rPiece = 1.0f / (float)texNoRow;

	arrNoColumns = columns;
	arrNoRows = rows;

	arrSize = arrNoColumns*arrNoRows;
	numElements = arrSize * 6;

	VertexPU* verts;

	verts = new VertexPU[numElements];

	float l, t, r, b, zz;

	int sZ = 1;
	int s = 0;
	zz = 0.0f;


	RectF sR;
	curCol = 0;
	curRow = 0;
	for (int i = 0; i < arrSize; i++) {
		s = i * 6;


		int tLocX = (dataArray[i] % texNoCol);//-1;
		int tLocY = (dataArray[i] / texNoCol);


		sR.l = tLocX * cPiece;
		sR.t = tLocY * rPiece;
		sR.r = sR.l + cPiece;
		sR.b = sR.t + rPiece;

		l = curCol * sZ;
		t = -(curRow)* sZ;
		r = l + sZ;
		b = t - sZ;

		verts[s] = { XMFLOAT3(l, t, zz), XMFLOAT2(sR.l, sR.t) };
		verts[s + 1] = { XMFLOAT3(r, t, zz), XMFLOAT2(sR.r, sR.t) };
		verts[s + 2] = { XMFLOAT3(l, b, 0), XMFLOAT2(sR.l, sR.b) };

		verts[s + 3] = { XMFLOAT3(l, b , zz), XMFLOAT2(sR.l, sR.b) };
		verts[s + 4] = { XMFLOAT3(r, t, zz), XMFLOAT2(sR.r, sR.t) };
		verts[s + 5] = { XMFLOAT3(r, b, zz), XMFLOAT2(sR.r, sR.b) };


		if (curCol < arrNoColumns - 1) curCol++;
		else {
			curCol = 0;
			curRow++;
		}

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
	device->CreateBuffer(&bd, &InitData, &m_vertexBuffer);


	*/

}

void TileBatch::SetResources(){
	



	//if (dat->_curTex != m_textureID) {
	context->PSSetShaderResources(0, 1, dat.GetTexture(m_textureID)->textureResource.GetAddressOf());
	dat._curTex = m_textureID;
	//}
	//if (dat->_curVS != m_vsID) {
	context->VSSetShader(dat.GetVertexShader(m_vsID)->vertexShader.Get(), 0, 0);
	context->IASetInputLayout(dat.GetVertexShader(m_vsID)->inputLayout.Get());
	dat._curVS = m_vsID;
	//}
	//if (dat->_curPS != m_psID) {
	context->PSSetShader(dat.GetPixelShader(m_psID)->pixelShader.Get(), 0, 0);
	dat._curPS = m_psID;
	//}
	//if (dat->_curTopo != m_topoID) {
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	dat._curTopo = m_topoID;
	//}

	UINT stride = sizeof(VertexPU);
	UINT offset = 0;
	//context->VSSetConstantBuffers(0, 1, cbPerMesh.GetAddressOf());
	context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);

}




void TileBatch::Draw() {
	context->VSSetConstantBuffers(0, 1, cbPerMesh.GetAddressOf());
	SetResources();

	x = 0;
	y = 0;
	x = 0;

	XMMATRIX fMat = XMMatrixTranslation(x, y, z) * camera->GetCameraScreenMatrix();
	//XMMATRIX fMat = XMLoadFloat4x4(&world) * cameraScreenMatrix;
	VS_C_BUFFER cb;
	XMStoreFloat4x4(&cb.wvp, fMat);

	context->UpdateSubresource(cbPerMesh.Get(), 0, 0, &cb, 0, 0);
	context->VSSetConstantBuffers(0, 1, cbPerMesh.GetAddressOf());

	context->Draw(numElements, 0);


}

void TileBatch::Update()
{
}
