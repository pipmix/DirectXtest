#pragma once
#include <dinput.h>

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

extern HINSTANCE hInst;
extern HWND hWnd;

class Input {

public:

	Input();
	~Input();


	void DetectInput(double time);


	IDirectInputDevice8* GetMouse();
	IDirectInputDevice8* GetKeyboard();
	void SetLastState(DIMOUSESTATE);


private:

	IDirectInputDevice8* DIKeyboard;
	IDirectInputDevice8* DIMouse;
	DIMOUSESTATE mouseLastState;
	LPDIRECTINPUT8 DirectInput;

};

