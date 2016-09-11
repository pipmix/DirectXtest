#pragma once

#pragma once
#include "Headers.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Data.h"

extern ComPtr<ID3D11Buffer> constantBuffer_finalMatrix;
extern Data* dat;

extern Camera* camera;

class Sprite {

public:

			Sprite();
	void	Create(UINT texID, UINT vsID, UINT psID);
	void	SetSourceRect(int i, UINT t);
	void	SetResources();

	void	Draw(float x, float y, float z);


	UINT	m_textureID;
	UINT	m_vsID;
	UINT	m_psID;
	UINT	m_topoID;
	Box		m_sourceRect;

	UINT numElements;

	ComPtr<ID3D11Buffer>		vertexBuffer;
	XMFLOAT3 _position;


};

