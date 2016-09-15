#include "Player.h"



void Player::Init()
{
	pv = { 0 };
}

void Player::Update(){




	float time = timer.GetDelta();

	if (pv.cBottom)pv.onGround = 1;
	if (pv.cLeft || pv.cRight)pv.onWall = 1;
	else wallTouchReset = 1;

	if (pv.onGround)canDoubleJump = false;

	if (input.isConnected) {

		m_vel.x += (cMoveSpeedX * time * input.b.leftStickFloatX);
		//m_vel.y += (cMoveSpeedX * time * input.b.leftStickFloatY);
		if (input.b.x)m_vel.x *= cRunSpeed;

	}

	if (input.b.a) {
		if (pv.onGround && jumpReset ) {
			m_vel.y = 0.22;
			pv.onGround = false;
			jumpReset = 0;
			canDoubleJump = true;
			jumping = true;
		}


		if (pv.cLeft) {
			if (!pv.onGround && wallJumpReset && wallTouchReset) {
				m_vel.x = cMoveSpeedX * time ;
				m_vel.y = 0.22f;
				wallTouchReset = 0;
			}

		}
		if (pv.cRight) {
			if (!pv.onGround && wallJumpReset && wallTouchReset) {
				m_vel.x = -(cMoveSpeedX * time);
				m_vel.y = 0.22f;
				wallTouchReset = 0;
			}

		}



		
	}
	else {
		jumpReset = 1;
		wallJumpReset = 1;
	}




	m_vel.y += (cFallSpeedY*time);
	if (pv.cLeft || pv.cRight)m_vel.y *= 0.75f;

	//if (m_vel.y > (cFallSpeedY*time*40))m_vel.y = (cFallSpeedY*time);

	// SlowDown
	m_vel.x *= 0.02;


	if (input.b.y) {

		SetPos(3.0f, 2.0f, 0.0f);
		m_vel = { 0.0f,0.0f, 0.0f };
	}



	m_pos.x += m_vel.x;
	m_pos.y += m_vel.y;
	UpdateCollision();

	pv = { 0 };
	

}

void Player::UpdateCollision(){



	m_collision.left = m_pos.x;
	m_collision.top = m_pos.y;
	m_collision.right = m_collision.left + 1.0f;
	m_collision.bottom = m_collision.top - 1.0f;



}

Rect Player::GetCollision(){
	return m_collision;
}


void Player::AddVelocity(float vx, float vy, float vz) {
	m_vel.x += vx;
	m_vel.y += vy;
	m_vel.z += vz;
}
void Player::SetVelocity(float vx, float vy, float vz) {
	m_vel = { vx, vy, vz };

}