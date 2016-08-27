#include "Camera.h"


Camera::Camera() {


	RECT rc = { 0,0,0,0 };
	GetClientRect(hWnd, &rc);
	mWindowWidth = rc.right;
	mWidowHeight = rc.bottom;




	//worldMatrix = XMMatrixIdentity();

	XMVECTOR Pos = XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	cameraMatrix = XMMatrixLookAtLH(Pos, At, Up);

	fov = XMConvertToRadians(45);
	aspectRatio = static_cast<float>(rc.right) / static_cast<float>(rc.bottom);
	nearClip = 0.1f;
	farClip = 1000.0f;
	//screenMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV2, mWindowWidth / (FLOAT)mWidowHeight, 0.01f, 100.0f);
	screenMatrix = XMMatrixPerspectiveFovLH(fov, 1.15f, nearClip, farClip);
	

	
	cameraScreenMatrix = cameraMatrix * screenMatrix;



}


void Camera::Update() {

	//cameraScreenMatrix = cameraMatrix * screenMatrix;


	/*
	ConstantBuffer cb;
	cb.world =			XMMatrixTranslation(0.0f, 0.0f, 0.0f);//XMMatrixTranspose(worldMatrix);
	cb.cameraScreen =	XMMatrixTranspose(cameraMatrix);
	//cb.cameraScreen =	cameraMatrix * screenMatrix;
	cb.screen =			XMMatrixTranspose(screenMatrix);

	cb.world = worldMatrix * cameraMatrix * screenMatrix;

	context->UpdateSubresource(constantBuffer.Get(), 0, nullptr, &cb, 0, 0);
	*/

}
void Camera::Draw() {

	context->VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());

}