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
	_numTex = _numPS = _numVS = 0;
	_Textures = new Texture*[_numTex];
	_PShaders = new PixelShader*[_numPS];
	_VShaders = new VertexShader*[_numVS];

}

const Texture* Data::GetTexture(int n){
	return _Textures[n];
}

const PixelShader * Data::GetPixelShader(int n){
	return _PShaders[n];
}

const VertexShader * Data::SetVertexShader(int n){
	return _VShaders[n];
}
