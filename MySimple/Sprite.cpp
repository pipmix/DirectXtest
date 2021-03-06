#include "Sprite.h"

Sprite::Sprite(){

	m_sourceRect = { 0.0f, 0.0f, 1.0f, 1.0f };
	m_topoID = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;

}

void Sprite::Create(){

	RectF dim;
	dim.l = 0.0f;
	dim.t = 1.0f;
	dim.r = 1.0f;
	dim.b = 0.0f;

	float zd = 0.0f;

	VertexPU verts[] = {


		{ XMFLOAT3(dim.l, dim.t, zd),		XMFLOAT2(m_sourceRect.x	, m_sourceRect.y) },
		{ XMFLOAT3(dim.r, dim.t, zd),		XMFLOAT2(m_sourceRect.x + m_sourceRect.w, m_sourceRect.y) },
		{ XMFLOAT3(dim.l, dim.b, zd),		XMFLOAT2(m_sourceRect.x	, m_sourceRect.y + m_sourceRect.h) },
		{ XMFLOAT3(dim.r, dim.b, zd),		XMFLOAT2(m_sourceRect.x + m_sourceRect.w, m_sourceRect.y + m_sourceRect.h) }


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

void Sprite::AssignTexture(UINT texID) {
	m_textureID = texID;

}
void Sprite::AssignVertextShader(UINT vsID) {
	m_vsID = vsID;

}
void Sprite::AssignPixelShader(UINT psID) {
	m_psID = psID;
}

void Sprite::AssignResources(UINT texID, UINT vsID, UINT psID) {
	AssignTexture(texID);
	AssignVertextShader(vsID);
	AssignPixelShader(psID);
}


void Sprite::SetResources(){

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
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		dat._curTopo = m_topoID;
	//}

	UINT stride = sizeof(VertexPU);
	UINT offset = 0;
	//context->VSSetConstantBuffers(0, 1, cbPerMesh.GetAddressOf());
	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	





}

void Sprite::SetPos(float x, float y, float z) {
	m_pos = { x, y, z };
}

void Sprite::MovePos(float x, float y, float z) {

	m_pos.x += x;
	m_pos.y += y;
	m_pos.z += z;

}

void Sprite::Draw(){

	SetResources();

	XMMATRIX fMat = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z) * camera->GetCameraScreenMatrix();

	VS_C_BUFFER cb;
	XMStoreFloat4x4(&cb.wvp, fMat);

	context->UpdateSubresource(cbPerMesh.Get(), 0, 0, &cb, 0, 0);

	context->Draw(numElements, 0);

}

void Sprite::QuickDraw(XMFLOAT3 p) {

	

	XMMATRIX fMat = XMMatrixTranslation(p.x, p.y, p.z) * camera->GetCameraScreenMatrix();

	VS_C_BUFFER cb;
	XMStoreFloat4x4(&cb.wvp, fMat);
	context->UpdateSubresource(cbPerMesh.Get(), 0, 0, &cb, 0, 0);

	context->Draw(numElements, 0);

}

void Sprite::SetSourceRect(int i) {

	m_sourceRect = dat.GetTexture(m_textureID)->GetSourceRectIndex(i);

}