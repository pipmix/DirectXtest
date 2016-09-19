#pragma once
#include "Texture.h"
#include "Shader.h"



class Data{
public:
						Data			();
						~Data			();
	void				LoadData		();

	Texture*		GetTexture		(int n);
	PixelShader*	GetPixelShader	(int n);
	VertexShader*	GetVertexShader	(int n);

	int _curTex = -1;
	int _curPS = -1;
	int _curVS = -1;
	int _curTopo = -1;



private:

	Texture**			_Textures;
	PixelShader**		_PShaders;
	VertexShader**		_VShaders;
	void LoadShaders();
	void LoadTextures();

	int _numTex, _numPS, _numVS;




};