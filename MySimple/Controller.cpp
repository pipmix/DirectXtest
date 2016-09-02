#include "Controller.h"

Controller::Controller()
{

	
}




void Controller::Update(){


	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(0, &state);

	LX = state.Gamepad.sThumbLX;
	LY = state.Gamepad.sThumbLY;
	
	if (dwResult != ERROR_SUCCESS) {
		isConnected = 0;
		Reset();
		return;
	}


	
	isConnected = true;

	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) b.left = 1; else b.left = 0;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)b.right = 1; else b.right = 0;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) b.up = 1; else b.up = 0;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)b.down = 1; else b.down = 0;

	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) b.a = 1; else b.a = 0;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)b.b = 1; else b.b = 0;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)b.x = 1; else b.x = 0;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)b.y = 1; else b.y = 0;

	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START)b.start = 1; else b.start = 0;


	if (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) b.leftTrigger = state.Gamepad.bLeftTrigger / 255.0f;
	else b.leftTrigger = 0.0f;


	if (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) b.leftTrigger = state.Gamepad.bLeftTrigger / 255.0f;
	else b.leftTrigger = 0.0f;

	b.lStick = 0;
	if (abs(state.Gamepad.sThumbLX) <= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
		b.lStick = 1;
		b.leftX = state.Gamepad.sThumbLX / 255;
	}
	if (abs(state.Gamepad.sThumbLY) <= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
		b.lStick = 1;
		b.leftY = state.Gamepad.sThumbLY / 255;
	}





	float deadZone = 0.1f;
	if ((state.Gamepad.sThumbLX < deadZone && state.Gamepad.sThumbLX > -deadZone) &&
		(state.Gamepad.sThumbLY < deadZone && state.Gamepad.sThumbLY > -deadZone)){
		b.leftX = 0;
		b.leftY = 0;
	}
	else {
		b.leftX = state.Gamepad.sThumbLY;
		b.leftY = state.Gamepad.sThumbLY;
	}


	





	if (b.a && prev_b.a) bs_A = held_;
	else if (b.a && !prev_b.a) bs_A = down_;
	else if (!b.a && prev_b.a) bs_A = released_;
	else bs_A = up_;

	prev_b = b;






	

	float LX = state.Gamepad.sThumbLX;
	float LY = state.Gamepad.sThumbLY;
	float magnitude = sqrt(LX*LX + LY*LY);
	float normalizedLX = LX / magnitude;
	float normalizedLY = LY / magnitude;

	float normalizedMagnitude = 0;

	
	if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE){
		
		if (magnitude > 32767) magnitude = 32767;
		magnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

		normalizedMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		b.lStick = 1;
	}
	else {
		magnitude = 0.0;
		normalizedMagnitude = 0.0;
		b.lStick = 0;
	}

	b.leftX = normalizedLX;
	b.leftY = normalizedLY;






		


}


void Controller::Reset() {


}


