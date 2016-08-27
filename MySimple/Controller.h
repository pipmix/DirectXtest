#pragma once
#include "Headers.h"

#include <Xinput.h>
#pragma comment(lib, "xinput9_1_0.lib")

extern bool LL;
extern bool RR;
extern bool UU;


struct ControllerButtons {


		bool a;
		bool b;
		bool x;
		bool y;

		bool l3;
		bool r3;


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
	void FilterDeadZone();

	ControllerButtons b;


	bool                    isConnected;
	
	XINPUT_STATE            inputState; 
	UINT64                  timeCheck; 
};