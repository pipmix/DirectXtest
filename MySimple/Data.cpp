#include "Data.h"

Data::Data(): _Textures(nullptr), _PShaders(nullptr), _VShaders(nullptr) {

}

Data::~Data(){

	for (int i = 0; i < _numTex; i++) {
		delete _Textures[i];
		_Textures[i] = nullptr;
	}
	delete [] _Textures;
	_Textures = nullptr;

	for (int i = 0; i < _numPS; i++) {
		delete _PShaders[i];
		_PShaders[i] = nullptr;
	}
	
	delete[] _PShaders;
	_PShaders = nullptr;

	for (int i = 0; i < _numVS; i++) {
		_VShaders[i] == nullptr;
		delete _VShaders[i];
	}
	delete[] _VShaders;
	_VShaders = nullptr;


}

void Data::LoadData(){
	_numTex = 5;
	_numPS = 2;
	_numVS = 3;
	_Textures = new Texture*[_numTex];
	_PShaders = new PixelShader*[_numPS];
	_VShaders = new VertexShader*[_numVS];

	LoadShaders();
	LoadTextures();
}



Texture* Data::GetTexture(int n){
	return _Textures[n];
}

PixelShader * Data::GetPixelShader(int n){
	return _PShaders[n];
}

VertexShader * Data::GetVertexShader(int n){
	return _VShaders[n];
}

void Data::LoadShaders(){

	_VShaders[D_VS_PUV] = new VertexShader(L"VS_PUV", VT_PU);
	_VShaders[D_VS_BASICMATRIX] = new VertexShader(L"VS_BasicMatrix", VT_P);
	_VShaders[D_VS_BASIC] = new VertexShader(L"VS_Basic", VT_P);

	_PShaders[D_PS_BASIC] = new PixelShader(L"PS_Basic");
	_PShaders[D_PS_PUV] = new PixelShader(L"PS_PUV");


}

void Data::LoadTextures()
{
	_Textures[D_TEX_BOX1] = new Texture();
	_Textures[D_TEX_BOX1]->Load(L"box1");


	_Textures[D_TEX_SET] = new Texture();
	_Textures[D_TEX_SET]->Load(L"set");
	_Textures[D_TEX_SET]->SetInfo(7,6,16,16);


	_Textures[D_TEX_ITEMS] = new Texture();
	_Textures[D_TEX_ITEMS]->Load(L"items_8c8r_16x16t");

	_Textures[D_TEX_ITEMS]->SetInfo(8, 8, 16, 16);

	_Textures[D_TEX_CHAR1] = new Texture();
	_Textures[D_TEX_CHAR1]->Load(L"walkTest");
	_Textures[D_TEX_CHAR1]->SetInfo(8, 8, 16, 16);
	
	
	
	
}
