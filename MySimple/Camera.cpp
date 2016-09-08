#include "Camera.h"


Camera::Camera() {


	RECT rc = { 0,0,0,0 };
	GetClientRect(hWnd, &rc);

	_IsCamPerspective	= true;
	_IsCamLookAt		= true;
	_CamPosition		= XMFLOAT3(0.0f, 0.0f, -10.0f);
	_CamLookAt			= XMFLOAT3(0.0f, 0.0f, 0.0f);
	_CamUpVector		= XMFLOAT3(0.0f, 1.0f, 0.0f);
	_CamFOVangle		= XMConvertToRadians(45);
	_CamAspectRatio		= static_cast<float>(rc.right) / static_cast<float>(rc.bottom);
	_CamNearClip		= 0.01f;
	_CamFarClip			= 1000.0f;

	UpdateAllMatrices();

}

void Camera::UpdateCameraMatrix() {

	XMStoreFloat4x4(&_CameraMatrix,  XMMatrixLookAtLH(XMLoadFloat3(&_CamPosition), XMLoadFloat3(&_CamLookAt), XMLoadFloat3(&_CamUpVector)));

}
void Camera::UpdateScreenMatrix() {
	
	if (_IsCamPerspective) XMStoreFloat4x4(&_ScreenMatrix, XMMatrixPerspectiveFovLH(_CamFOVangle, _CamAspectRatio, _CamNearClip, _CamFarClip));
	else XMStoreFloat4x4(&_ScreenMatrix, XMMatrixOrthographicLH(20, 10, _CamNearClip, _CamFarClip));

}

void Camera::UpdateCameraScreenMatrix(){

	XMStoreFloat4x4(&_CameraScreenMatrix, GetCameraMatrix() * GetScreenMatrix());

}

void Camera::UpdateAllMatrices(){
	UpdateCameraMatrix();
	UpdateScreenMatrix();
	UpdateCameraScreenMatrix();
}

const XMMATRIX Camera::GetCameraScreenMatrix(){

	return XMLoadFloat4x4(&_CameraScreenMatrix);
}

const XMMATRIX Camera::GetCameraMatrix(){

	return XMLoadFloat4x4(&_CameraMatrix);
}

const XMMATRIX Camera::GetScreenMatrix(){

	return XMLoadFloat4x4(&_ScreenMatrix);

}


void Camera::Update() {



}
void Camera::Draw() {


}

void Camera::MoveTo(float posX, float posY, float posZ)
{


}

void Camera::MoveBy(float vecX, float vecY, float vecZ)
{

	_CamPosition.x += vecX;
	_CamPosition.y += vecY;
	_CamPosition.z += vecZ;

	_CamLookAt.x += vecX;
	_CamLookAt.y += vecY;

	UpdateAllMatrices();
}

