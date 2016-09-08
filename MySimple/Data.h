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
	const Texture*		GetTexture		(int n);
	const PixelShader*	GetPixelShader	(int n);
	const VertexShader*	GetVertexShader	(int n);

	



private:

	Texture**			_Textures;
	PixelShader**		_PShaders;
	VertexShader**		_VShaders;
	void LoadShaders();

	int _numTex, _numPS, _numVS;



};