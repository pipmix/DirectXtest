#include "Texture.h"


Texture::Texture(std::wstring fn){


	std::wstring s = gPath + L"Images/" + fn + L".dds";

	HRESULT hr = CreateDDSTextureFromFile(device.Get(), s.c_str(), NULL, &textureResource, NULL);
	if (hr) Error(L"Texture Load Error", s.c_str());


}

void Texture::SetInfo(int columns, int rows, int width, int height) {

	_columns = columns;
	_rows = rows;
	_width = width;
	_height = height;
	if (columns > 0 && rows > 0)_IsTileMap = true;
	else _IsTileMap = false;

}


