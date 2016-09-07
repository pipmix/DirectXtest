#pragma once

#include "Headers.h"


void ReadDataFromFile(LPCWSTR filename, byte** data, UINT* size);

void Error(LPCWSTR header, LPCWSTR info);