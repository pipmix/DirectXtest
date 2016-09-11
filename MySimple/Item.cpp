#include "Item.h"

void Item::Create(float x, float y, float z, ObjectType ot){

	_position = { x, y, z };
	_velocity = { 0.0f, 0.0f, 0.0f };

	switch (ot)
	{

	case OT_chest:
		break;
	case OT_coin:
		_collision = { 0.0f, 0.0f, 1.0f, 1.0f };
		break;
	case OT_sword:
		break;
	default:
		break;

	}
}

void ObjCoin::Create(float x, float y, float z){
	_position	=	{ x, y, z };
	_velocity	=	{ 0.0f, 0.0f, 0.0f };
	_collision	=	{ 0.0f, 0.0f, 1.0f, 1.0f };
	_textureID	=	D_TEX_BRICK;
	_vsID		=	D_VS_PUV;
	_psID		=	D_PS_PUV;
	_sourceRect =	{ 0.0f, 0.0f, 1.0f, 1.0f };
}
