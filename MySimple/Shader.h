#pragma once
#include "Headers.h"
#include "DataTypes.h"
#include "Helpers.h"


extern ComPtr<ID3D11Device>			device;
extern ComPtr<ID3D11DeviceContext>	context;

extern ComPtr<ID3D11Buffer> constantBuffer_finalMatrix;
extern XMMATRIX cameraMatrix;
extern XMMATRIX screenMatrix;
extern XMMATRIX cameraScreenMatrix;

extern HWND hWnd;
extern HINSTANCE hInst;


class Shader {



public:

	Shader();


	void Draw();
	void Update();

	ComPtr<ID3D11VertexShader>	vertexShader;
	ComPtr<ID3D11PixelShader>	pixelShader;

	ComPtr<ID3D11Buffer>		vertexBuffer;
	ComPtr<ID3D11InputLayout>	inputLayout;

	UINT numElements;



};

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