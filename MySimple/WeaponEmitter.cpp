#include "WeaponEmitter.h"

WeaponEmitter::WeaponEmitter()
{
}

void WeaponEmitter::Initialize(){

	for (int i = 0; i < 50; i++) {
		p[i].isAlive = 1;
		p[i].isVisible = 1;
		p[i].SetSpeed(GetRealDist(0.01f, 2.0f));
		p[i].SetAngle(GetRealDist(0.0f, XM_2PI));

	}

	spr.AssignResources(D_TEX_ITEMS, D_VS_PUV, D_PS_PUV);
	spr.SetSourceRect(10);
	spr.Create();
	
}

void WeaponEmitter::Update() {
	for (int i = 0; i < 50; i++) {
		p[i].Update();
	}
}

void WeaponEmitter::Draw() {
	for (int i = 0; i < 50; i++) {
		spr.QuickDraw(p[i].pos);
	}
}