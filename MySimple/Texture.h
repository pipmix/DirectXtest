#pragma once

#include "Headers.h"
#include "Helpers.h"

extern ComPtr<ID3D11Device>			device;
extern ComPtr<ID3D11DeviceContext>	context;

extern ComPtr<ID3D11Buffer> constantBuffer_finalMatrix;
extern XMMATRIX cameraMatrix;
extern XMMATRIX screenMatrix;
extern XMMATRIX cameraScreenMatrix;

class Texture {



public:

	Texture(std::wstring fn);
	void SetInfo(int columns, int rows, int width, int height);

	ComPtr<ID3D11ShaderResourceView>	textureResource;
	int _columns, _rows, _width, _height;
	bool _IsTileMap;

};


