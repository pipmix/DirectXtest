#pragma once
#include "Sprite.h"
#include "Timer.h"
#include "Controller.h"
#include "Shape.h"

extern ComPtr<ID3D11Device>			device;
extern ComPtr<ID3D11DeviceContext>	context;
extern Timer timer;
extern Controller input;

const float cJumpSpd = -3.3f;
const float cWallJumpSpd = -2.7f;
const float cWallJumpY = 2.4f;
const float cJumpY = -2.7f; 

const float cMoveSpeedX = 0.2f;
const float cFallSpeedY = -0.0005f;
const float cRunSpeed = 1.8f;


class Player : public Sprite { 

public:
	void	Init();
	void	Update();
	void	UpdateCollision();
	Rect	GetCollision();

	void	AddVelocity(float vx, float vy, float vz);
	void	SetVelocity(float vx, float vy, float vz);


	Rect m_collision = { 0.0f, 0.0f, 1.0f, -1.0f };
	XMFLOAT3 m_vel = { 0.0f, 0.0f, 0.0f };


	bool m_onGround = 0;

};