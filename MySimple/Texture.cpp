#include "Texture.h"


Texture::Texture(std::wstring fn ){


	std::wstring s = gPath + L"Images/" + fn + L".dds";

	HRESULT hr = CreateDDSTextureFromFile(device.Get(), s.c_str(), NULL, &textureResource, NULL);
	if (hr) Error(L"Texture Load Error", s.c_str());


}


