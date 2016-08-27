#pragma once
#include "Headers.h"
#include "Shader.h"
#include "Camera.h"
#include "RectData.h"


extern ComPtr<ID3D11Device>			device;
extern ComPtr<ID3D11DeviceContext>	context;

extern ComPtr<ID3D11Buffer>			constantBuffer;

extern HWND hWnd;
extern HINSTANCE hInst;

extern XMMATRIX cameraScreenMatrix;;
extern XMMATRIX cameraMatrix;
extern XMMATRIX screenMatrix;

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





	D3D11_VIEWPORT viewport;

	Shader* shader;
	Camera* camera;
	RectData* rd1;
	RectData* rd2;

	long mWindowWidth;
	long mWidowHeight;


};