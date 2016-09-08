#include "Data.h"

Data::Data(): _Textures(nullptr), _PShaders(nullptr), _VShaders(nullptr) {

}

Data::~Data(){

	for (int i = 0; i < _numTex; i++) delete _Textures[i];
	delete [] _Textures;

	for (int i = 0; i < _numPS; i++) delete _PShaders[i];
	delete[] _PShaders;

	for (int i = 0; i < _numVS; i++) delete _VShaders[i];
	delete[] _VShaders;


}

void Data::LoadData(){
	_numTex = 0;
	_numPS = 2;
	_numVS = 3;
	_Textures = new Texture*[_numTex];
	_PShaders = new PixelShader*[_numPS];
	_VShaders = new VertexShader*[_numVS];

	LoadShaders();

}

void Data::Update()
{

}

void Data::Draw()
{
}

const Texture* Data::GetTexture(int n){
	return _Textures[n];
}

const PixelShader * Data::GetPixelShader(int n){
	return _PShaders[n];
}

const VertexShader * Data::GetVertexShader(int n){
	return _VShaders[n];
}

void Data::LoadShaders(){

	_VShaders[D_VS_PUV] = new VertexShader(L"VS_PUV", VT_PU);
	_VShaders[D_VS_BASICMATRIX] = new VertexShader(L"VS_BasicMatrix", VT_P);
	_VShaders[D_VS_BASIC] = new VertexShader(L"VS_Basic", VT_P);

	_PShaders[D_PS_BASIC] = new PixelShader(L"PS_Basic");
	_PShaders[D_PS_PUV] = new PixelShader(L"PS_PUV");


}
