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

	float l = 0.0f, t = 0.0f, r = 1.0f, b = -1.0f, zz = -0.001f;


	VertexP verts[] ={

		XMFLOAT3(l,t,zz),
		XMFLOAT3(r,t,zz),
		
		XMFLOAT3(r,b,zz),
		XMFLOAT3(l,b,zz),
		XMFLOAT3(l,t,zz)


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
	context->VSSetConstantBuffers(0, 1, constantBuffer_finalMatrix.GetAddressOf());
	context->PSSetShader(pixelShader.Get(), 0, 0);

	context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	context->IASetInputLayout(inputLayout.Get());




	XMMATRIX fMat = XMMatrixTranslation(0, 0, 0) * camera->GetCameraScreenMatrix();
	VS_C_BUFFER cb;
	XMStoreFloat4x4(&cb.wvp, fMat);

	context->UpdateSubresource(constantBuffer_finalMatrix.Get(), 0, 0, &cb, 0, 0);

	

	context->Draw(numElements, 0);


	

}

void Shader::Update() {




}



VertexShader::VertexShader(std::wstring fn, VertexType vt){


	std::wstring fileName = L"C:/Shaders/" + fn + L".cso";

	UINT8*	vsData;
	UINT	vsDataLength;

	ReadDataFromFile(fileName.c_str(), &vsData, &vsDataLength);

	device->CreateVertexShader(vsData, vsDataLength, nullptr, &vertexShader);

	switch (vt){

	case VT_P:
		device->CreateInputLayout(VertexP_Layout, ARRAYSIZE(VertexP_Layout), vsData, vsDataLength, &inputLayout);
		break;
	case VT_PU:
		device->CreateInputLayout(VertexPU_Layout, ARRAYSIZE(VertexPU_Layout), vsData, vsDataLength, &inputLayout);
		break;
	case VT_PNU:
		break;
	default:
		break;
	};

	

};

PixelShader::PixelShader(std::wstring fn) {

	std::wstring fileName = L"C:/Shaders/" + fn + L".cso";

	UINT8*	psData;
	UINT	psDataLength;

	ReadDataFromFile(fileName.c_str(), &psData, &psDataLength);

	device->CreatePixelShader(psData, psDataLength, nullptr, &pixelShader);

}