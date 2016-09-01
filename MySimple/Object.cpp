#include "Object.h"

Object::Object()
{
	p = new Particle();
	//y = -3;
}

void Object::Update()
{
	//dx += cont0->LX;
	//float t = 0.0f;
	if (cont0->b.left)dx -= 2.3;
	
	if (cont0->b.right)dx += 2.3;
	dx *= 0.02;

	//if (ctrl.b.a)dx -= 0.3;
	dy += -0.0002;

	if (y < -3) dy = 0.03;



	x += dx;
	y += dy;
}

void Object::Draw()
{

	//p->Draw(x, y, 0.0f);
	p->Draw(x, y, -2.0f);
	//p->Draw(2, -1, 0.0f);
	//p->Draw(3, -1, 0.0f);
	//p->Draw(4, -2, 0.0f);

	p->Draw(x-2, y-2, 0.0f);

}
