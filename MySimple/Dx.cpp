#include "Dx.h"



Dx::Dx(HWND h) : m_hWnd(h) {}

void Dx::Initialize() {

	UpdateWindowInfo();


	// Device and Swapchain
	DXGI_SWAP_CHAIN_DESC scd = { 0 };
	scd.BufferCount = 1;
	scd.BufferDesc.Width = m_windowW;
	scd.BufferDesc.Height = m_windowH;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = m_hWnd;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = TRUE;
	D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, 0, 0, D3D11_SDK_VERSION, &scd, m_swapChain.GetAddressOf(), device.GetAddressOf(), NULL, context.GetAddressOf());

	device->CreateDeferredContext(0, &dContext);

	// Backbuffer
	ComPtr<ID3D11Texture2D> backBufferTexture;
	m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBufferTexture.GetAddressOf()));
	device->CreateRenderTargetView(backBufferTexture.Get(), nullptr, m_backBuffer.ReleaseAndGetAddressOf());

	// Zbuffer
	D3D11_TEXTURE2D_DESC zBufferDesc = { 0 };
	zBufferDesc.Width = m_windowW;
	zBufferDesc.Height = m_windowH;
	zBufferDesc.ArraySize = 1;
	zBufferDesc.MipLevels = 1;
	zBufferDesc.SampleDesc.Count = 1;
	zBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	zBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	ComPtr<ID3D11Texture2D> zbuffertexture;
	device->CreateTexture2D(&zBufferDesc, nullptr, &zbuffertexture);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	device->CreateDepthStencilView(zbuffertexture.Get(), &dsvd, m_zBuffer.GetAddressOf());


	game.Load();

}


void Dx::Update() {
	//deltaTime = timer.GetDelta();
	game.Update();
}


void Dx::Draw() {

	ClearFrame();
	game.Draw();


	dContext->FinishCommandList(FALSE, &m_commandList);
	context->ExecuteCommandList(m_commandList.Get(), TRUE);
	m_swapChain->Present(1, 0);


}

void Dx::ClearFrame() {


	float fill[4] = { 0.0f, 0.2f, 0.25f, 1.0f };

	dContext->ClearRenderTargetView(m_backBuffer.Get(), fill);
	dContext->ClearDepthStencilView(m_zBuffer.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	dContext->OMSetRenderTargets(1, m_backBuffer.GetAddressOf(), m_zBuffer.Get());

	CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_windowW), static_cast<float>(m_windowH));
	dContext->RSSetViewports(1, &viewport);

}

void Dx::UpdateWindowInfo() {

	RECT rc = { 0 };
	GetWindowRect(m_hWnd, &rc);
	m_windowW = rc.right - rc.left;
	m_windowH = rc.bottom - rc.top;

	GetClientRect(m_hWnd, &rc);
	m_clientW = rc.right - rc.left;
	m_clientH = rc.bottom - rc.top;


}


