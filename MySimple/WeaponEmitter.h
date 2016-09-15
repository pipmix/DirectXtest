#pragma once
#include "Headers.h"
#include "Part.h"
#include "Sprite.h"


class WeaponEmitter {

public:
	WeaponEmitter();
	void Initialize();

	void Update();
	void Draw();

	float m_colRadius;
	Part p[50];
	Sprite spr;

	bool isActive = 0;

};