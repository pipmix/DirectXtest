#pragma once

#include "Headers.h"
#include "Helpers.h"

extern ComPtr<ID3D11Device>			device;
extern ComPtr<ID3D11DeviceContext>	context;

extern ComPtr<ID3D11Buffer> cbPerMesh;
extern XMMATRIX cameraMatrix;
extern XMMATRIX screenMatrix;
extern XMMATRIX cameraScreenMatrix;

class Texture {



public:

	Texture();
	void Load(std::wstring fn);
	void LoadAsync(std::wstring fn);
	void SetInfo(int columns, int rows, int width, int height);
	Box GetSourceRectIndex(int index);
	Box GetSourceRectIndex(int index_X, int index_Y);

	ComPtr<ID3D11ShaderResourceView>	textureResource;
	ComPtr<ID3D11Resource>	texRes;
	int _columns, _rows, _width, _height;
	//normalized x y width height 
	float _nX, _nY, _nW, _nH;
	bool _IsTileMap;
	int pixelW;
	int pixelH;
	bool hasAlpha;
	bool usesPreMul;

};


