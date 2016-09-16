#pragma once
#include "Headers.h"
#include "DataTypes.h"
#include "Helpers.h"



extern ComPtr<ID3D11Device>			device;
extern ComPtr<ID3D11DeviceContext>	context;

extern ComPtr<ID3D11Buffer> cbPerMesh;

extern HWND hWnd;
extern HINSTANCE hInst;



class PixelShader {
public:

	PixelShader(std::wstring fn);
	ComPtr<ID3D11PixelShader>	pixelShader;

};

class VertexShader {
public:
	VertexShader(std::wstring fn, VertexType vt);

	ComPtr<ID3D11VertexShader>	vertexShader;
	ComPtr<ID3D11InputLayout>	inputLayout;

};