#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
{
	m_sourceRect = { 0.0f, 0.0f, 1.0f, 1.0f };
	m_topoID = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
}

void AnimatedSprite::Create(){


	dim.l = 0.0f;
	dim.t = 1.0f;
	dim.r = 1.0f;
	dim.b = 0.0f;

	zd = 0.0f;

	VertexPU verts[] = {

		{ XMFLOAT3(dim.l, dim.t, zd),		XMFLOAT2(m_sourceRect.x	, m_sourceRect.y) },
		{ XMFLOAT3(dim.r, dim.t, zd),		XMFLOAT2(m_sourceRect.x + m_sourceRect.w, m_sourceRect.y) },
		{ XMFLOAT3(dim.l, dim.b, zd),		XMFLOAT2(m_sourceRect.x	, m_sourceRect.y + m_sourceRect.h) },
		{ XMFLOAT3(dim.r, dim.b, zd),		XMFLOAT2(m_sourceRect.x + m_sourceRect.w, m_sourceRect.y + m_sourceRect.h) }


	};
	numElements = ARRAYSIZE(verts);

	D3D11_BUFFER_DESC bd = { 0 };
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	
	bd.ByteWidth = sizeof(VertexPU) * numElements;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = verts;
	device->CreateBuffer(&bd, &InitData, &vertexBuffer);
}

void AnimatedSprite::AssignResources(UINT texID, UINT vsID, UINT psID) {
	m_textureID = texID;
	m_vsID = vsID;
	m_psID = psID;
}

void AnimatedSprite::Update(){

}

void AnimatedSprite::Draw(){

}

void AnimatedSprite::UpdateVertexBuffer(){


		VertexPU verts[] = {


			{ XMFLOAT3(dim.l, dim.t, zd),		XMFLOAT2(m_sourceRect.x	, m_sourceRect.y) },
			{ XMFLOAT3(dim.r, dim.t, zd),		XMFLOAT2(m_sourceRect.x + m_sourceRect.w, m_sourceRect.y) },
			{ XMFLOAT3(dim.l, dim.b, zd),		XMFLOAT2(m_sourceRect.x	, m_sourceRect.y + m_sourceRect.h) },
			{ XMFLOAT3(dim.r, dim.b, zd),		XMFLOAT2(m_sourceRect.x + m_sourceRect.w, m_sourceRect.y + m_sourceRect.h) }


		};
		numElements = ARRAYSIZE(verts);

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

		context->Map(vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy(mappedResource.pData, verts, sizeof(VertexPU) * numElements);
		context->Unmap(vertexBuffer.Get(), 0);
	

}

void AnimatedSprite::SetResources() {

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