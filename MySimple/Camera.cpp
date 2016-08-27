#include "Camera.h"


Camera::Camera() {


	RECT rc = { 0,0,0,0 };
	GetClientRect(hWnd, &rc);
	mWindowWidth = rc.right;
	mWidowHeight = rc.bottom;




	worldMatrix = XMMatrixIdentity();

	XMVECTOR Eye = XMVectorSet(0.0f, 1.0f, -5.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	cameraMatrix = XMMatrixLookAtLH(Eye, At, Up);
	screenMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV2, mWindowWidth / (FLOAT)mWidowHeight, 0.01f, 100.0f);

	

	

	CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
	device->CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer);


}


void Camera::Update() {



	ConstantBuffer cb;
	cb.world = XMMatrixTranspose(worldMatrix);
	cb.camera = XMMatrixTranspose(cameraMatrix);
	cb.screen = XMMatrixTranspose(screenMatrix);

	context->UpdateSubresource(constantBuffer.Get(), 0, nullptr, &cb, 0, 0);


}
void Camera::Draw() {

	context->VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());

}