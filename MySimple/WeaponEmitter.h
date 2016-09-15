#pragma once
#include "Headers.h"
#include "Part.h"
#include "Sprite.h"
#include "Timer.h"
extern Timer timer;

class WeaponEmitter {

public:
	WeaponEmitter();
	void Initialize();
	void Reset();

	void Update();
	void Draw();

	float m_colRadius;
	Part p[50];
	Sprite spr;

	bool isActive = 0;
	float t;

	int numPart;
	int numDead;

};