#pragma once
#include "Texture.h"
#include "DataTypes.h"
#include "Input.h"
#include "Timer.h"
#include "Particle.h"
#include "Controller.h"
#include "Data.h"
#include "Map.h"

extern ComPtr<ID3D11Device>			device;
extern ComPtr<ID3D11DeviceContext>	context;
extern Timer timer;
extern Controller* cont0;

class Object {

public:

	Object();
	void Update();
	void Draw();

	float x = 0.0f, y = 0.0f;
	float  dx = 0.0f, dy = 0.0f;
	
	RectI sourceRect = { 0 };

	bool hasGravity = 0;

	Particle* p;

	bool onGround = 0;
	float timeSinceLastFrame;


	bool canJump, dblJump, wallJump, wallslide;
	float _jumpSpd = -3.3f;
	float _wallJumpSpd = -2.7f;
	float h_wjump = 2.4f;
	float v_fjump = -2.7f; // -2.65

	float cMoveSpeedX = 0.2f;
	float cFallSpeedY = -0.0005f;
	float cRunSpeed = 1.8f;

	Map* map01;
};