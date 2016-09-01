#include "Object.h"

Object::Object()
{
	p = new Particle();
	//y = -3;
}

void Object::Update()
{


	x = 2;
	dy += -0.0002;

	if (y < -2) dy = 0.03;



	x += dx;
	y += dy;
}

void Object::Draw()
{

	//p->Draw(x, y, 0.0f);
	p->Draw(x, y, 0.0f);
	//p->Draw(2, -1, 0.0f);
	//p->Draw(3, -1, 0.0f);
	//p->Draw(4, -2, 0.0f);

	p->Draw(0, 0, -0.2f);

}
