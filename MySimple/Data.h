#pragma once
#include "Texture.h"
#include "Shader.h"


class Data{
public:
						Data			();
						~Data			();
	void				LoadData		();
	const Texture*		GetTexture		(int n);
	const PixelShader*	GetPixelShader	(int n);
	const VertexShader*	SetVertexShader	(int n);

private:

	Texture**			_Textures;
	PixelShader**		_PShaders;
	VertexShader**		_VShaders;

	int _numTex, _numPS, _numVS;



};