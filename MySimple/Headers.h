#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>
#include <string>
#include <stdint.h>
#include <random>
#include <chrono>
#include <vector>
#include <wrl.h>
#include <string>
#include <memory>
#include <fstream>
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <DirectXCollision.h>
#include <wrl\client.h>
#include "DDSTextureLoader.h"


#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

using namespace DirectX;
using Microsoft::WRL::ComPtr;


const std::wstring gPath = L"C:/Box/Box Sync/Data/";
const float GRAV = 0.2f;
