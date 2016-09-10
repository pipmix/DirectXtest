#pragma once
#include "Headers.h"
using namespace std;

struct TextData {

		int unicodeId;
		float uCoord;
		float vCoord; 
		float texCharWidth;
		float texCharHeight;
		float scrCharWidth;
		float scrCharHeight;
		float leftOffset;
		float topOffset;
		float xMove;
};

struct TextKern{
	int firstid;
	int secondid;
	float amount;
};

class Text {
public:
	void LoadFont();

};