#include "Game.h"


Game::Game() {

	RECT rc = { 0,0,0,0 };
	GetClientRect(hWnd, &rc);
	mWindowWidth = rc.right;
	mWidowHeight = rc.bottom;

	// Device Resources
	// Create Device and Swapchain
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = mWindowWidth;
	swapChainDesc.BufferDesc.Height = mWidowHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;
	D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, 0, 0, D3D11_SDK_VERSION, &swapChainDesc, swapChain.GetAddressOf(), device.GetAddressOf(), NULL, context.GetAddressOf());


	ComPtr<ID3D11Texture2D> backBuffer;
	swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));
	device->CreateRenderTargetView(backBuffer.Get(), nullptr, backBuffer_RT.ReleaseAndGetAddressOf());


	viewport.Width = (FLOAT)mWindowWidth;
	viewport.Height = (FLOAT)mWidowHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;


	//ZBUFFER
	D3D11_TEXTURE2D_DESC zBufferDesc = { 0 };
	zBufferDesc.Width = mWindowWidth;
	zBufferDesc.Height = mWidowHeight;
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
	device->CreateDepthStencilView(zbuffertexture.Get(), &dsvd, zbuffer.GetAddressOf());
	// End Zbuffer




	D3D11_RASTERIZER_DESC rd;
	rd.FillMode = D3D11_FILL_WIREFRAME;
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = FALSE;
	rd.DepthClipEnable = TRUE;
	rd.ScissorEnable = FALSE;



	device->CreateRasterizerState(&rd, &RS_default);

	camera = new Camera();
	shader = new Shader();
}


void Game::Update() {

	camera->Update();

}
void Game::Draw() {

	float fill[4] = { 0.0f, 0.2f, 0.25f, 1.0f };

	context->ClearRenderTargetView(backBuffer_RT.Get(), fill);
	context->ClearDepthStencilView(zbuffer.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	context->OMSetRenderTargets(1, backBuffer_RT.GetAddressOf(), zbuffer.Get());

	context->RSSetViewports(1, &viewport);
	//context->RSSetState(RS_default.Get());





	camera->Draw();
	shader->Draw();






	swapChain->Present(1, 0);


}