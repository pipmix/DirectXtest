#include "Object.h"

Object::Object(){

	p = new Particle();
	canJump, dblJump, wallJump, wallslide = 1;
}

void Object::Update(){

	XMFLOAT4 tCol = p->collision;

	float time = timer.GetDelta();

	if (input.isConnected) {


		//if (cont0->b.left)dx *= (1 * cMoveSpeedX * time);
		//if (cont0->b.right)dx *= (1.0f * cMoveSpeedX * time);
		//if (cont0->b.leftStickIntX != 0)
		//dx += (cMoveSpeedX * time * cont0->b.leftStickIntX);
		dx += (cMoveSpeedX * time * input.b.leftStickFloatX);

		if (input.b.x)dx *= cRunSpeed;

	}



	
	dx *= 0.02;

	//if (ctrl.b.a)dx -= 0.3;
	//dy += -0.0002;

	if (!onGround) dy += (cFallSpeedY*time);
	else {
		dy = 0;
		if (input.b.a) {

				dy = 0.15;
				onGround = false;
			
		}
	
	}



	//if (y < -3) dy = 0.03;

	if (y < -5) onGround = 1;





	

	x += dx;
	y += dy;


	float moveZ = (-input.b.leftTriggerFloat) + input.b.rightTriggerFloat;
	camera->MoveBy(input.b.rightStickFloatX, input.b.rightStickFloatY, moveZ);

	XMFLOAT2 mc = camera->ConvertMouseCoord(XMFLOAT2{ input.m_md.m_screenX, input.m_md.m_screenY });
	input.m_md.m_screenX = mc.x;
	input.m_md.m_screenY = mc.y;

}

void Object::Draw()
{


	p->Draw(x, y, -0.001f);
	XMVECTOR v1 = { input.m_md.m_screenX * 0.01f, input.m_md.m_screenY * 0.01f, 0.0f };
	XMVECTOR v2 = { input.m_md.m_screenX * 1000.0f, input.m_md.m_screenY * 1000.0f, 0.0f };


	DirectX::XMMatrixInverse(&v1, camera->GetCameraMatrix());
	DirectX::XMMatrixInverse(&v2, camera->GetCameraMatrix());

	xmvectorno
	
	p->Draw((float)input.m_md.m_screenX, (float)input.m_md.m_screenY, -0.02f);


}
