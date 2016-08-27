#include "Shader.h"

Shader::Shader(){


	LPCWSTR filenameVS = L"C:/Shaders/VS_BasicMatrix.cso";
	LPCWSTR filenamePS = L"C:/Shaders/PS_Basic.cso";
	
	UINT8*	vsData;
	UINT	vsDataLength;

	UINT8*	psData;
	UINT	psDataLength;

	ReadDataFromFile(filenameVS, &vsData, &vsDataLength);
	ReadDataFromFile(filenamePS, &psData, &psDataLength);

	device->CreateVertexShader(vsData, vsDataLength, nullptr, &vertexShader);
	device->CreatePixelShader(psData, psDataLength, nullptr, &pixelShader);



	VertexP verts[] ={

		XMFLOAT3(-0.5f, 0.5f, 0.0f),
		XMFLOAT3(0.5f, 0.5f, 0.0f),
		
		XMFLOAT3(0.5f, -0.5f, 0.0f),
		XMFLOAT3(-0.5f, -0.5f, 0.0f),
		XMFLOAT3(-0.5f, 0.5f, 0.0f)


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
	


	device->CreateInputLayout(VertexP_Layout, ARRAYSIZE(VertexP_Layout), vsData, vsDataLength, &inputLayout);
	

}

void Shader::Draw() {

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	UINT stride = sizeof(VertexP);
	UINT offset = 0;

	
	context->VSSetShader(vertexShader.Get(), 0, 0);
	context->PSSetShader(pixelShader.Get(), 0, 0);

	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	context->IASetInputLayout(inputLayout.Get());

	

	context->Draw(numElements, 0);


	

}

void Shader::Update() {




}


