#include "Controller.h"

Controller::Controller()
{
}




void Controller::Update(){


	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(0, &state);

	if (dwResult != ERROR_SUCCESS) return;


	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)LL = 1;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)RR = 1;


}





