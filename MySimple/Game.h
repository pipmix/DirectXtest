#pragma once
#include "Headers.h"
#include "Shader.h"
#include "Camera.h"
#include "RectData.h"
#include "Controller.h"


extern ComPtr<ID3D11Device>			device;
extern ComPtr<ID3D11DeviceContext>	context;



extern HWND hWnd;
extern HINSTANCE hInst;


class Game {

public:
		Game();


	void Update();
	void Draw();

	void Clear();



private:

	ComPtr<IDXGISwapChain>			swapChain;

	ComPtr<ID3D11RenderTargetView>	backBuffer_RT;
	ComPtr<ID3D11DepthStencilView>	zbuffer;

	ComPtr<ID3D11RasterizerState>	RS_default;
	ComPtr<ID3D11RasterizerState>	RS_wireframe;

	ComPtr<ID3D11SamplerState>		samplerState;
	ComPtr<ID3D11DepthStencilState> depthStencilState;



	D3D11_VIEWPORT viewport;

	Shader* shader;
	Camera* camera;
	RectData* rd1;
	RectData* rd2;
	RectData* rd3;

	Controller* controller;

	long mWindowWidth;
	long mWidowHeight;


};