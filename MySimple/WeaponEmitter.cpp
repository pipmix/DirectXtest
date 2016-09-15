#include "WeaponEmitter.h"

WeaponEmitter::WeaponEmitter()
{
}

void WeaponEmitter::Initialize(){


	numPart = 50;
	Reset();
	t = 0.0f;
	
	spr.AssignResources(D_TEX_ITEMS, D_VS_PUV, D_PS_PUV);
	spr.SetSourceRect(10);
	spr.Create();
	
}

void WeaponEmitter::Update() {

	if (numDead == numPart)return;

	float tmp = timer.GetDelta();
	t += tmp;
	for (int i = 0; i < 50; i++) {
		if (p[i].isAlive) {
			p[i].Update(tmp);
			if (t > p[i].lifeTime) {
				p[i].isAlive = 0;
				numDead++;
			}
		}
	}
}

void WeaponEmitter::Draw() {
	
	if (numDead == numPart) return;
	for (int i = 0; i < numPart; i++) {
		if (p[i].isAlive == 0)continue;
		spr.SetResources();
		spr.QuickDraw(p[i].pos);

	}
}

void WeaponEmitter::Reset() {

	for (int i = 0; i < numPart; i++) {
		p[i].pos = { 0.0f, 0.0f, 0.0f };
		p[i].isAlive = 1;
		p[i].isVisible = 1;
		p[i].lifeTime = GetRealDist(0.01f, 2000.0f);
		p[i].SetSpeed(GetRealDist(0.01f, 3.0f));
		p[i].SetAngle(GetRealDist(0.0f, XM_2PI));
	}
	t = 0.0f;
	numDead = 0;
}