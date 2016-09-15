#pragma once
#include "Part.h"
#include "Sprite.h"
#include "Timer.h"

extern Timer timer;

class Gun {

public:
			Gun();
	void	Init();
	void	Draw();
	void	Update();
	void	Fire();
	void	SetPos(XMFLOAT3 position);

	void	Reset();

	Part*	GetAllRadius();

private:

	Part p[25];
	Sprite spr;

	int currentBullet;
	int numBullets;
	float timeBeforeShot;
	float timePool;
	float totalTime;
	XMFLOAT3 pos;

	bool atStart = 1;
	int retCount = 0;

};