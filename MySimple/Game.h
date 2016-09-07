#pragma once
#include "Headers.h"
#include "Shader.h"
#include "Camera.h"
#include "RectData.h"
#include "Controller.h"
#include "Texture.h"
#include "Particle.h"
#include "Timer.h"
#include "Input.h"
#include "Object.h"
#include "TileBatch.h"

extern ComPtr<ID3D11Device>			device;
extern ComPtr<ID3D11DeviceContext>	context;

extern Timer timer;
extern Controller* cont0;


extern HWND hWnd;
extern HINSTANCE hInst;
extern Camera* camera;


class Game {

public:
		Game();
		~Game();


	void Update();
	void Draw();

	void Clear();

	void Close();



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
	RectData* rd1;
	//RectData* rd2;
	//RectData* rd3;
	//Particle* particle;


	Object* player;

	Texture* tex;
	TileBatch* tileBatch;

	Controller* controller;

	long mWindowWidth;
	long mWidowHeight;


};