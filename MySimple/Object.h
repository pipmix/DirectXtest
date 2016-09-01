#pragma once
#include "Texture.h"
#include "DataTypes.h"
#include "Input.h"
#include "Timer.h"
#include "Particle.h"
extern ComPtr<ID3D11Device>			device;
extern ComPtr<ID3D11DeviceContext>	context;
extern Timer timer;
extern Input input;

class Object {

public:

	Object();
	void Update();
	void Draw();

	float x = 0.0f, y = 0.0f, dx = 0.0f, dy = 0.0f;
	RectF collision = { 0 };
	RectI sourceRect = { 0 };

	bool hasGravity = 0;

	Particle* p;



};