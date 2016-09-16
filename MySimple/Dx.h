#pragma once
#include "Headers.h"
#include "Gme.h"
using namespace DirectX;
using Microsoft::WRL::ComPtr;

extern ComPtr<ID3D11Device>			device;
extern ComPtr<ID3D11DeviceContext>	context;
extern ComPtr<ID3D11Buffer>			gCBperMesh;

class Dx {


public:

			Dx(HWND h);
	void	Initialize();
	void	Update();
	void	Draw();
	void	ClearFrame();
	void	UpdateWindowInfo();

	void	CreateStates();


private:


	ComPtr<IDXGISwapChain>			m_swapChain;
	ComPtr<ID3D11RenderTargetView>	m_backBuffer;
	ComPtr<ID3D11DepthStencilView>	m_zBuffer;
	ComPtr<ID3D11RasterizerState>	RS_default;
	ComPtr<ID3D11SamplerState>		samplerState;
	ComPtr<ID3D11DepthStencilState> depthStencilState;

	Gme game;

	HWND m_hWnd;

	long m_clientW, m_clientH, m_windowH, m_windowW;

	

};