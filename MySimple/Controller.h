#pragma once
#include "Headers.h"

#include <Xinput.h>
#pragma comment(lib, "xinput9_1_0.lib")

extern bool LL;
extern bool RR;
extern bool UU;


enum bState{
	down_, up_, released_, held_
};


struct ControllerButtons {


		bool a;
		bool b;
		bool x;
		bool y;
		bool l3;
		bool r3;

		bool lStick;
		bool rStick;

		float leftTrigger;
		bool leftShoulder;

		float rightTrigger;
		bool rightShoulder;

		bool select;
		bool start;

		bool left;
		bool up;
		bool right;
		bool down;

		float leftX;
		float leftY;
		float rightX;
		float rightY;

};


class Controller {


public:


	Controller();

	void Update();
	//void FilterDeadZone();
	void Reset();

	ControllerButtons b;
	ControllerButtons prev_b;


	bool                    isConnected = 0;
	
	XINPUT_STATE            inputState; 
	UINT64                  timeCheck; 


	bState bs_A = up_;

	float LX = 0.0f;
	float LY = 0.0f;
};