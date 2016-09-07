#include "Controller.h"

Controller::Controller()
{

	
}




void Controller::Update(){

	b = { 0 };
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(0, &state);



	if (dwResult != ERROR_SUCCESS) {
		isConnected = 0;
		Reset();
		return;
	} // Return if not connected

	isConnected = true;
	

	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) b.left = 1; 
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)b.right = 1;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) b.up = 1;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)b.down = 1;

	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)b.a = 1; 
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)b.b = 1; 
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)b.x = 1; 
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)b.y = 1; 

	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START)b.start = 1; else b.start = 0;


	if (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) b.leftTrigger = state.Gamepad.bLeftTrigger / 255.0f;
	else b.leftTrigger = 0.0f;


	if (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) b.leftTrigger = state.Gamepad.bLeftTrigger / 255.0f;
	else b.leftTrigger = 0.0f;

	short leftDead = 1000;

	// Left Stick
		// Left X
		if (abs(state.Gamepad.sThumbLX) >= 8000) {
			b.leftStickFloatX = (float)state.Gamepad.sThumbLX / (float)32767;
			if (b.leftStickFloatX > 0)b.leftStickIntX = 1;
			else b.leftStickIntX = -1;
		}
		// Left Y
		if (abs(state.Gamepad.sThumbLY) >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
			b.leftStickFloatY = state.Gamepad.sThumbLY / 32767;
			if (b.leftStickFloatY > 0)b.leftStickIntY= 1;
			else b.leftStickIntY = -1;
		}
	// Right Stick
		// Right X
		if (abs(state.Gamepad.sThumbRX) >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
			b.rightStickFloatX = state.Gamepad.sThumbRX / 32767;
			if (b.rightStickFloatX > 0)b.rightStickIntX = 1;
			else b.rightStickIntX = -1;
		}
		// Right Y
		if (abs(state.Gamepad.sThumbRY) >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
			b.rightStickFloatY = state.Gamepad.sThumbRY / 32767;
			if (b.rightStickFloatY > 0)b.rightStickIntY = 1;
			else b.rightStickIntY = -1;
		}
		
/*
	if (b.a && prev_b.a) bs_A = held_;
	else if (b.a && !prev_b.a) bs_A = down_;
	else if (!b.a && prev_b.a) bs_A = released_;
	else bs_A = up_;

	prev_b = b;

	*/

}


void Controller::Reset() {


}


