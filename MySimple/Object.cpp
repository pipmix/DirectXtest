#include "Object.h"

Object::Object(){

	p = new Particle();
	canJump, dblJump, wallJump, wallslide = 1;
}

void Object::Update(){

	float time = timer.GetDelta();

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


	float moveZ = (-cont0->b.leftTriggerFloat) + cont0->b.rightTriggerFloat;
	camera->MoveBy(cont0->b.rightStickFloatX, cont0->b.rightStickFloatY, moveZ);


}

void Object::Draw()
{


	p->Draw(x, y, -0.001f);


}
