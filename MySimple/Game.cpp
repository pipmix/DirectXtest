#include "Game.h"


Game::Game() {

	CreateEngine();
	CreateGame();

}

void Game::CreateEngine() {

	RECT rc = { 0,0,0,0 };
	GetWindowRect(hWnd, &rc);
	mWindowWidth = rc.right - rc.left;
	mWindowHeight = rc.bottom - rc.top;

	// Create Device and Swapchain
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = mWindowWidth;
	swapChainDesc.BufferDesc.Height = mWindowHeight;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 1;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 10;
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
	viewport.Height = (float)mWindowHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;

	// Create Zbuffer
	D3D11_TEXTURE2D_DESC zBufferDesc = { 0 };
	zBufferDesc.Width = mWindowWidth;
	zBufferDesc.Height = mWindowHeight;
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
	context->VSSetConstantBuffers(1, 1, cbScreen.GetAddressOf());

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


	// Blend States
	D3D11_BLEND_DESC bsd;
	ZeroMemory(&bsd, sizeof(D3D11_BLEND_DESC));

	bsd.RenderTarget[0].BlendEnable = FALSE;
	bsd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	device->CreateBlendState(&bsd, &blendS_solid);

	// Post Process 
	D3D11_BUFFER_DESC ppbd = { 0 };
	
	ppbd.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
	ppbd.StructureByteStride = sizeof(float);
	ppbd.ByteWidth = ( 4 * (mWindowWidth * mWindowHeight) ) / (16 * 1024);
	ppbd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	
	
	
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

	//cont0 = new Controller;

	map01 = new Map();
	map01->LoadMap();

	player->map01 = map01;

	ls3 = new LineShape3d;
	ls3->Create();

	ls3o = new LineShape3dOutline;
	ls3o->Create();

	item01.Create(5.0f, 5.0f, 0.0f, OT_coin);

	
	spr01.AssignResources(D_TEX_ITEMS, D_VS_PUV, D_PS_PUV);
	spr01.SetSourceRect(10);
	spr01.Create();

	spr01.SetPos(2.0f, 10.0f, 0.0f);

	we.Initialize();

	gun.Init();

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
	//delete cont0;
	delete dat;
	
	dat = nullptr;
	//delete tex;

	//delete controller;
}


void Game::Update() {

	camera->SetTarget(spr01.m_pos.x, spr01.m_pos.y, spr01.m_pos.z);
	camera->MoveTowardsTarget();

	int aS = 6;
	Rect* rArr;
	rArr = new Rect[aS];
	rArr [0] = { 0.0f, -5.0f, 6.0f, -10.0f };
	rArr [1] = { 6.0f, -3.0f, 9.0f, -10 };
	rArr [2] = { 10.0f, -6.0, 14.0f, -10 };

	rArr[3] = { -10.0f, 11.0f, 22.0f, 2 };
	rArr[4] = { 7.0f, 15.0f, 9.0f, -10 };
	rArr[5] = { -15.0f, 14.0, -1.0f, -3 };


	if (input.b.b)we.Reset();
	
	we.Update();


	timer.Update();
	input.Update();
	camera->Update();

	spr01.Update();

	rd1->Update();
	shape01->Update();
	shape02->Update();

	tileBatch->Update();

	player->Update();
	map01->Update();

	spr01.UpdateCollision();
	
	
	Rect r1 = spr01.GetCollision();
	Box b1;
	b1.x = r1.left;
	b1.y = r1.top;
	b1.w = r1.right - r1.left;
	b1.h = -(r1.bottom - r1.top);

	Box b2;

	for (int i = 0; i < aS; i++) {
		
		float he = rArr[i].bottom - rArr[i].top;
		b2.x = rArr[i].left;
		b2.y = he + rArr[i].top;
		b2.w = rArr[i].right - rArr[i].left;
		b2.h = -(rArr[i].bottom - rArr[i].top);

		XMFLOAT2 velocity = { 0.0f, 0.0f };
		float l = b2.x - (b1.x + b1.w);
		float r = (b2.x + b2.w) - b1.x;
		float t = b2.y - (b1.y + b1.h);
		float b = (b2.y + b2.h) - b1.y;
		if (l > 0 || r < 0 || t > 0 || b < 0) {
			continue;
		}
		else {
			velocity.x = abs(l) < r ? l : r;
			velocity.y = abs(t) < b ? t : b;


			if (abs(velocity.x) < abs(velocity.y)) {
				velocity.y = 0.0f;

				// wall jump
				//spr01.m_vel.y = 0.0f;
				//spr01.m_vel.x = 0.0f;
			}
			else {
				velocity.x = 0.0f;
				// going up
				if (!(spr01.m_vel.y > 0.0f))spr01.m_vel.y = 0.0f;
				
			}

			//if (velocity.y > 0.0f )spr01.m_vel.y = 0.0f;
			// means collision along x
			if (velocity.x > 0.0f) {
				spr01.pv.cLeft = 1;
				spr01.m_vel.x = 0.0f;
			}
			else if (velocity.x < 0.0f) {
				spr01.pv.cRight = 1;
				spr01.m_vel.x = 0.0f;
			}
			if (velocity.y < 0.0f)spr01.pv.cTop = 1;
			else if (velocity.y > 0.0f)spr01.pv.cBottom = 1;

			spr01.MovePos(velocity.x, velocity.y, 0.0f);
			spr01.UpdateCollision();
			r1 = spr01.GetCollision();
			b1;
			b1.x = r1.left;
			b1.y = r1.top;
			b1.w = r1.right - r1.left;
			b1.h = -(r1.bottom - r1.top);
		}
	}

	gun.SetPos(spr01.m_pos);
	gun.Update();

	if (input.b.x)gun.Fire();
	


}
void Game::Draw() {

	Clear();
	context->PSSetSamplers(0, 1, samplerState.GetAddressOf());
	context->RSSetState(RS_default.Get());



	we.Draw();
	//tileBatch->Draw();

	//player->Draw();
	
	spr01.Draw();
	map01->Draw();
	
	ls3o->Draw();
	gun.Draw();
	
	swapChain->Present(1, 0);


}
void Game::Clear() {

	float fill[4] = { 0.0f, 0.2f, 0.25f, 1.0f };
	context->ClearRenderTargetView(backBuffer_RT.Get(), fill);
	context->ClearDepthStencilView(zbuffer.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, backBuffer_RT.GetAddressOf(), zbuffer.Get());
	context->RSSetViewports(1, &viewport);


}

void Game::Close()
{

}

