#include "Texture.h"


Texture::Texture(std::wstring fn ){


	std::wstring s = gPath + L"Images/" + fn + L".dds";

	CreateDDSTextureFromFile(device.Get(), s.c_str(), NULL, &textureResource, NULL);



}


