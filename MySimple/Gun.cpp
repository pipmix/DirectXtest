#include "Gun.h"

Gun::Gun()
{
}

void Gun::Init()
{
	spr.AssignResources(D_TEX_ITEMS, D_VS_PUV, D_PS_PUV);
	spr.SetSourceRect(10);
	spr.Create();

	numBullets = 25;
	currentBullet = 0;
	timeBeforeShot = 500.0f;
	timePool = 0.0f;

}

void Gun::Reset() {

	totalTime = 0.0f;
	for (int i = 0; i < numBullets; i++) {
		p[i].isAlive = 0;
		
	}

}

void Gun::Draw(){
	spr.SetResources();
	for (int i = 0; i < numBullets; i++) {
		if (p[i].isAlive) {
			spr.QuickDraw(p[i].pos);
		}
	}
}

void Gun::Update(){
	float tmp = timer.GetDelta();
	timePool += tmp;
	totalTime += tmp;

	for (int i = 0; i < numBullets; i++) {
		if (p[i].isAlive) {
			if (totalTime > p[i].lifeTime)
			p[i].Update(tmp);
		}
	}

}

void Gun::Fire(){

	if (timePool > timeBeforeShot) {
		timePool -= timeBeforeShot;
		p[currentBullet].isAlive = 1;
		p[currentBullet].SetAngle(0);
		p[currentBullet].SetSpeed(2.0f);
		p[currentBullet].lifeTime = GetRealDist(0.01f, 2000.0f);
		p[currentBullet].pos = pos;
		p[currentBullet].SetAcc(XMFLOAT3{ 0.0f,0.0f,0.0f });

		currentBullet++;
		if (currentBullet >= numBullets) {
			currentBullet = 0;
			totalTime = 0.0f;
		}

	}


}

void Gun::SetPos(XMFLOAT3 position) {
	pos = position;
}

Part* Gun::GetAllRadius() {

	if (retCount = numBullets) {
		retCount = 0;
		return nullptr;
	}
	Part* tmp = &p[retCount];
	retCount++;
	return tmp;
	
}
