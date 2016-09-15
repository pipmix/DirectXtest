#pragma once
#include "Headers.h"


class Part {



public:
			Part();
	void	Update();
	void	SetSpeed(float spd);
	void	SetAngle(float ang);

	bool isAlive = 0;
	bool isVisible = 0;

	float lifeTime;


	XMFLOAT3 pos;
	XMFLOAT3 vel;
	XMFLOAT3 acc;

};


