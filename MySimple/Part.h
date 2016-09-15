#pragma once
#include "Headers.h"


class Part {



public:
			Part();
	void	Update(float t);
	void	SetSpeed(float spd);
	void	SetAngle(float ang);
	void	SetAcc(XMFLOAT3 acceleration);

	bool isAlive = 0;
	bool isVisible = 0;

	float lifeTime;


	XMFLOAT3 pos;
	XMFLOAT3 vel;
	XMFLOAT3 acc;

};


