#include "Player.h"

void Player::Update(){


	float time = timer.GetDelta();

	if (input.isConnected) {

		m_vel.x += (cMoveSpeedX * time * input.b.leftStickFloatX);
		//m_vel.y += (cMoveSpeedX * time * input.b.leftStickFloatY);
		if (input.b.x)m_vel.x *= cRunSpeed;

	}

	m_vel.y += (cFallSpeedY*time);

	// SlowDown
	m_vel.x *= 0.02;
	//m_vel.y *= 0.02;
	//dy *= 0.5;
	
	// Gravity
	//if (!m_onGround) dy += (cFallSpeedY*time);
	//else dy = 0.0f;



	m_pos.x += m_vel.x;
	m_pos.y += m_vel.y;

	

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