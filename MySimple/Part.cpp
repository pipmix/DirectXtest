#include "Part.h"

Part::Part() : pos(0.0f, 0.0f, 0.0f), vel(0.0f, 0.0f, 0.0f), acc(0.0f, -0.06f, 0.0f) {


}





void Part::Update(float t)
{

	pos.x += vel.x * 0.01f * t;
	pos.y += vel.y * 0.01f * t;

	vel.x += acc.x;
	vel.y += acc.y;
}


void Part::SetSpeed(float spd) {
	float a = atan2(vel.y, vel.x); // angle
	vel.x = cos(a) * spd;
	vel.y = sin(a) * spd;
}

void Part::SetAngle(float ang) {
	float s = sqrt(vel.x*vel.x + vel.y * vel.y); // speed
	vel.x = cos(ang) * s;
	vel.y = sin(ang) * s;

}

void Part::SetAcc(XMFLOAT3 acceleration) {
	acc = acceleration;

}