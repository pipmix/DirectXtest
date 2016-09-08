#pragma once
#include "Texture.h"
#include "Shader.h"



class Data{
public:
						Data			();
						~Data			();
	void				LoadData		();
	void				Update			();
	void				Draw			();
	Texture*		GetTexture		(int n);
	PixelShader*	GetPixelShader	(int n);
	VertexShader*	GetVertexShader	(int n);

	



private:

	Texture**			_Textures;
	PixelShader**		_PShaders;
	VertexShader**		_VShaders;
	void LoadShaders();
	void LoadTextures();

	int _numTex, _numPS, _numVS;



};