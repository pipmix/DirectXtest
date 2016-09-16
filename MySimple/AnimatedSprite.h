#pragma once
#include "Headers.h"
#include "DataTypes.h"
#include "Data.h"
#include "Camera.h"

extern ComPtr<ID3D11Device>			device;
extern ComPtr<ID3D11DeviceContext>	context;
extern ComPtr<ID3D11Buffer> cbPerMesh;
extern Data* dat;

extern Camera* camera;

class AnimatedSprite {
public:
	
			AnimatedSprite();
	void	Create();
	void	Update();
	void	Draw();
	void	UpdateVertexBuffer();

	UINT						m_textureID;
	UINT						m_vsID;
	UINT						m_psID;
	UINT						m_topoID;
	Box							m_sourceRect;

	UINT						numElements;

	ComPtr<ID3D11Buffer>		vertexBuffer;
	XMFLOAT3					m_pos;
	RectF dim;

	float m_frameSpeed;
	float m_elapsedTime;
	float zd;

};