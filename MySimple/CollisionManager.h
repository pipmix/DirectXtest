#pragma once
#include "Headers.h"

enum COLLISION_TYPE {
	CT_Player, CT_Enemy, CT_StaticWorld
};

class CollisionManager {

public:

	void AddCollider(XMFLOAT4 c, COLLISION_TYPE ct);

};