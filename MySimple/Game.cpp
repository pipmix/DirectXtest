#include "Game.h"


Game::Game() {

	CreateEngine();
	CreateGame();

}

void Game::CreateEngine() {

	RECT rc = { 0,0,0,0 };
	GetClientRect(hWnd, &rc);
	mWindowWidth = rc.right - rc.left;
	mWidowHeight = rc.bottom - rc.top;

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

	// Create Backbuffer
	ComPtr<ID3D11Texture2D> backBuffer;
	swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));
	device->CreateRenderTargetView(backBuffer.Get(), nullptr, backBuffer_RT.ReleaseAndGetAddressOf());

	// Create Viewport
	viewport.Width = (float)mWindowWidth;
	viewport.Height = (float)mWidowHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;

	// Create Zbuffer
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

	// Create Samplers
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.MaxAnisotropy = 0;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.MinLOD = 0.0f;
	samplerDesc.MaxLOD = 0.0f;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;

	device->CreateSamplerState(&samplerDesc, &samplerState);

	// Create Constant buffers

	//CD3D11_BUFFER_DESC constantBufferDesc(sizeof(VS_C_BUFFER), D3D11_BIND_CONSTANT_BUFFER);
	//device->CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer_finalMatrix);
	D3D11_BUFFER_DESC bd1 = { 0 };

	bd1.Usage = D3D11_USAGE_DEFAULT;
	bd1.ByteWidth = sizeof(VS_C_BUFFER);
	bd1.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	device->CreateBuffer(&bd1, nullptr, &constantBuffer_finalMatrix);
	context->VSSetConstantBuffers(0, 1, constantBuffer_finalMatrix.GetAddressOf());

	D3D11_BUFFER_DESC bd = { 0 };

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(PS_C_BUFFER);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	device->CreateBuffer(&bd, nullptr, &cbScreen);
	context->PSSetConstantBuffers(1, 1, cbScreen.GetAddressOf());

	// Create Rasterizers

	D3D11_RASTERIZER_DESC rsd;
	rsd.FillMode = D3D11_FILL_SOLID;
	rsd.CullMode = D3D11_CULL_BACK;
	rsd.FrontCounterClockwise = false;
	rsd.DepthBias = false;
	rsd.DepthBiasClamp = 0;
	rsd.SlopeScaledDepthBias = 0;
	rsd.DepthClipEnable = true;
	rsd.ScissorEnable = true;
	rsd.MultisampleEnable = false;
	rsd.AntialiasedLineEnable = false;

	device->CreateRasterizerState(&rsd, &RS_default);

	rsd.FillMode = D3D11_FILL_WIREFRAME;
	device->CreateRasterizerState(&rsd, &RS_wireframe);

	D3D11_RASTERIZER_DESC rd;
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = FALSE;
	rd.DepthClipEnable = TRUE;
	rd.ScissorEnable = TRUE;
	//device->CreateRasterizerState(&rd, &RS_default);

	D3D11_RASTERIZER_DESC rd_w;
	rd_w.FillMode = D3D11_FILL_WIREFRAME;
	rd_w.CullMode = D3D11_CULL_BACK;
	rd_w.FrontCounterClockwise = FALSE;
	rd_w.DepthClipEnable = TRUE;
	rd_w.ScissorEnable = TRUE;
	//device->CreateRasterizerState(&rd_w, &RS_wireframe);

}

void Game::CreateGame() {


	camera = new Camera();
	// Shared textures and shaders
	dat = new Data();
	dat->LoadData();

	player = new Object;
	tileBatch = new TileBatch;
	tileBatch->LoadMap();

	rd1 = new RectData(0, 0, 4, 4);

	timer.Init();

	cont0 = new Controller;

	map01 = new Map();
	map01->LoadMap();

	player->map01 = map01;

	ls3 = new LineShape3d;
	ls3->Create();

	ls3o = new LineShape3dOutline;
	ls3o->Create();
}

Game::~Game()
{

	//delete shader;
	
	//delete rd1;
	//delete rd2;
	//delete  rd3;
	delete player;
	delete shape01;
	delete shape02;
	delete rd1;
	delete ls3, ls3o;
	delete camera;
	delete cont0;
	delete dat;
	
	dat = nullptr;
	//delete tex;

	//delete controller;
}


void Game::Update() {




	timer.Update();
	cont0->Update();
	//controller->Update();
	camera->Update();
	rd1->Update();
	shape01->Update();
	shape02->Update();
	//rd1->Update();
	//rd2->Update();
	//rd3->Update();

	player->Update();
	map01->Update();
	dat->Update();

}
void Game::Draw() {



	Clear();

	context->PSSetSamplers(0, 1, samplerState.GetAddressOf());
	
	context->RSSetState(RS_default.Get());



	//tileBatch->Draw();
	player->Draw();
	map01->Draw();
	//context->RSSetState(RS_wireframe.Get());

	ls3o->Draw();
	swapChain->Present(1, 0);


}
void Game::Clear() {

	float fill[4] = { 0.0f, 0.2f, 0.25f, 1.0f };

	context->ClearRenderTargetView(backBuffer_RT.Get(), fill);
	context->ClearDepthStencilView(zbuffer.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	context->OMSetRenderTargets(1, backBuffer_RT.GetAddressOf(), zbuffer.Get());

	context->RSSetViewports(1, &viewport);
	context->RSSetState(RS_wireframe.Get());
	//context->RSSetState(RS_default.Get());

}

void Game::Close()
{

}

