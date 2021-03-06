#pragma once
#include "DataTypes.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Data.h"
extern Data dat;


extern Camera* camera;


class TileBatch {


public:
	TileBatch();
	void LoadMap();
	void Create(int* dataArray, int columns, int rows);

	void SetResources();
	void Draw();
	void Update();

	int texSizeW = 0, texSizeH = 0;
	int texNoCol = 0, texNoRow = 0;

	int arrNoColumns= 0, arrNoRows = 0, arrSize = 0, tileW= 0, tileH = 0, curRow = 0, curCol = 0;
	int numElements;

	ComPtr<ID3D11Buffer>		m_vertexBuffer;

	//PixelShader* ps;
	//VertexShader* vs;
	//Texture* texture;

	float x = 0,	y = 0,	z = 0.0f ;

	UINT	m_textureID;
	UINT	m_vsID;
	UINT	m_psID;
	UINT	m_topoID;

	


};