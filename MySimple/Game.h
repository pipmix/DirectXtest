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
#include "Map.h"
#include "Data.h"
#include "Item.h"
#include "Sprite.h"
#include "Player.h"
#include "WeaponEmitter.h"
#include "Gun.h"


extern ComPtr<ID3D11Device>			device;
extern ComPtr<ID3D11DeviceContext>	context;
extern Data* dat;

extern Timer timer;
extern Controller input;


extern HWND hWnd;
extern HINSTANCE hInst;
extern Camera* camera;


class Game {

public:
		Game();
		~Game();

		void CreateEngine();
		void CreateGame();


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

	ComPtr<ID3D11Buffer>			cbScreen;
	ComPtr<ID3D11BlendState>		blendS_transparent;
	ComPtr<ID3D11BlendState>		blendS_solid;

	ComPtr<ID3D11Buffer>			m_postProcessBuffer;

	D3D11_VIEWPORT viewport;

	Player spr01;

	RectData* rd1;
	//RectData* rd2;
	//RectData* rd3;
	//Particle* particle;
	LineShape3d* ls3;
	LineShape3dOutline* ls3o;
	Shape* shape01;
	Shape* shape02;

	Gun gun;

	Map* map01;

	Item item01;

	Object* player;

	Texture* tex;
	TileBatch* tileBatch;

	Controller* controller;

	WeaponEmitter we;

	long mWindowWidth;
	long mWindowHeight;


};


