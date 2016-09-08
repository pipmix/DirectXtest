#include "Shader.h"







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