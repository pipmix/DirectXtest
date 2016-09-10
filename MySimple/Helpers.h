#pragma once

#include "Headers.h"


void ReadDataFromFile(LPCWSTR filename, byte** data, UINT* size);

void Error(LPCWSTR header, LPCWSTR info);

bool IntersectsFloat(XMFLOAT4& rectA, XMFLOAT4& rectB);

bool AABBIntersect2D(XMFLOAT4& rectA, XMFLOAT3& pos, XMFLOAT3& vel, XMFLOAT4& rectB );