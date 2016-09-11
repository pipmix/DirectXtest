#pragma once
#include "DataTypes.h"

class Item : GameObj {
	
public:

	void Create(float x, float y, float z, ObjectType ot);



};

class ObjCoin : GameObj {

public:
	void Create(float x, float y, float z);
	UINT _textureID;
	UINT _vsID;
	UINT _psID;
	Box _sourceRect;

};