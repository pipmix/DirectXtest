#include "Object.h"

Object::Object()
{
	p = new Particle();
	//y = -3;
}

void Object::Update(){

	float time = timer.GetDelta();
	//timeSinceLastFrame += timer.GetDelta();
	//dx += cont0->LX;
	//float t = 0.0f;
	if (cont0->isConnected) {


		//if (cont0->b.left)dx *= (1 * cMoveSpeedX * time);
		//if (cont0->b.right)dx *= (1.0f * cMoveSpeedX * time);
		//if (cont0->b.leftStickIntX != 0)
		//dx += (cMoveSpeedX * time * cont0->b.leftStickIntX);
		dx += (cMoveSpeedX * time * cont0->b.leftStickFloatX);

		if (cont0->b.x)dx *= cRunSpeed;

	}



	
	dx *= 0.02;

	//if (ctrl.b.a)dx -= 0.3;
	//dy += -0.0002;

	if (!onGround) dy += (cFallSpeedY*time);
	else {
		dy = 0;
		if (cont0->b.a) {

				dy = 0.15;
				onGround = false;
			
		}
	
	}



	//if (y < -3) dy = 0.03;

	if (y < -5) onGround = 1;



	x += dx;
	y += dy;
}

void Object::Draw()
{

	//p->Draw(x, y, 0.0f);
	p->Draw(x, y, -0.001f);
	//p->Draw(2, -1, 0.0f);
	//p->Draw(3, -1, 0.0f);
	//p->Draw(4, -2, 0.0f);

	p->Draw(x-2, y, 0.0f);

}
