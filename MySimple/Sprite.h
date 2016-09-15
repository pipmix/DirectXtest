#pragma once

#pragma once
#include "Headers.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Data.h"
#include "Shape.h"

extern ComPtr<ID3D11Buffer> constantBuffer_finalMatrix;
extern Data* dat;

extern Camera* camera;

class Sprite {

public:

			Sprite				();
	void	Create				();
	void	SetSourceRect		(int i);
	void	SetResources		();

	void	Draw				();
	void	SetPos				(float x, float y, float z);
	void	MovePos				(float x, float y, float z);

	void	AssignTexture		(UINT texID);
	void	AssignVertextShader	(UINT vsID);
	void	AssignPixelShader	(UINT psID);
	void	AssignResources		(UINT texID, UINT vsID, UINT psID);


	UINT						m_textureID;
	UINT						m_vsID;
	UINT						m_psID;
	UINT						m_topoID;
	Box							m_sourceRect;

	UINT						numElements;

	ComPtr<ID3D11Buffer>		vertexBuffer;
	XMFLOAT3					m_pos;
	ShapeRectangle* r1;


};

