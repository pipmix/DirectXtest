#pragma once
#include "DataTypes.h"
#include "Shader.h"
#include "Texture.h"




class TileBatch {




public:
	TileBatch();
	void LoadMap();

	void SetResources();
	void Draw();
	void Update();

	int texSizeW = 0, texSizeH = 0;
	int texNoCol = 0, texNoRow = 0;

	int arrNoColumns= 0, arrNoRows = 0, arrSize = 0, tileW= 0, tileH = 0, curRow = 0, curCol = 0;
	int numElements;

	ComPtr<ID3D11Buffer>		vBuffer;

	PixelShader* ps;
	VertexShader* vs;
	Texture* texture;

	float x = 0,	y = 0,	z = 0.0f ;
	


};