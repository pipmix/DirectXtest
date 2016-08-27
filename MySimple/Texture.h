#pragma once

#include "Headers.h"

extern ComPtr<ID3D11Device>			device;
extern ComPtr<ID3D11DeviceContext>	context;

class Texture {



public:

	Texture(std::wstring fn);

	ComPtr<ID3D11ShaderResourceView>	textureResource;

};


