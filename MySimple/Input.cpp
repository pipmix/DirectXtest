#include "Input.h"

Input::Input() {

	DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&DirectInput, NULL);
	DirectInput->CreateDevice(GUID_SysKeyboard, &DIKeyboard, NULL);
	DirectInput->CreateDevice(GUID_SysMouse, &DIMouse, NULL);
	DIKeyboard->SetDataFormat(&c_dfDIKeyboard);
	DIKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	DIMouse->SetDataFormat(&c_dfDIMouse);
	DIMouse->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);

}

Input::~Input() {

	DIKeyboard->Unacquire();
	DIMouse->Unacquire();
	DirectInput->Release();

}


void Input::DetectInput(double time) {
	DIMOUSESTATE mouseCurrState;
	BYTE keyboardState[256];

	DIKeyboard->Acquire();
	DIMouse->Acquire();

	DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseCurrState);

	DIKeyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);

	if (keyboardState[DIK_ESCAPE] & 0x80) {

	}


	if (keyboardState[DIK_LEFT] & 0x80)
	{

	}
	if (keyboardState[DIK_RIGHT] & 0x80)
	{

	}
	if (keyboardState[DIK_UP] & 0x80)
	{

	}
	if (keyboardState[DIK_DOWN] & 0x80)
	{

	}
	mouseLastState = mouseCurrState;


}

IDirectInputDevice8* Input::GetMouse() {
	return DIMouse;
}
IDirectInputDevice8* Input::GetKeyboard() {
	return DIKeyboard;
}