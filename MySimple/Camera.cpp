#include "Camera.h"


Camera::Camera() {


	RECT rc = { 0 };
	GetWindowRect(hWnd, &rc);

	_IsCamPerspective	= true;
	_IsCamLookAt		= true;
	_CamPosition		= XMFLOAT3(0.0f, 0.0f, -10.0f);
	_CamLookAt			= XMFLOAT3(0.0f, 0.0f, 0.0f);
	_CamUpVector		= XMFLOAT3(0.0f, 1.0f, 0.0f);
	_CamFOVangle		= XMConvertToRadians(45);
	_CamAspectRatio		= static_cast<float>(rc.right - rc.left) / static_cast<float>(rc.bottom - rc.top);
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

XMFLOAT2 Camera::ConvertMouseCoord(XMFLOAT2 mc){

	RECT rc = { 0 };
	GetWindowRect(hWnd, &rc);
	float w2 = static_cast<float>(rc.right - rc.left) / 2;
	float h2 = static_cast<float>(rc.bottom - rc.top);
		

	return XMFLOAT2{
	tanf(_CamFOVangle*0.5f)*(mc.x / w2 - 1.0f) / _CamAspectRatio,
	tanf(_CamFOVangle*0.5f)*(1.0f - mc.y / h2)

	};


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

void Camera::SetTarget(float tx, float ty, float tz) {

	_target = { tx, ty, tz };
}
void Camera::MoveTowardsTarget() {

	float catchUpX;
	float catchUpY;
	float distanceX = roundf(abs(_CamPosition.x - _target.x));
	float distanceY = roundf(abs(_CamPosition.y - _target.y));

	if (distanceX >= 32)	catchUpX = 6.0f;
	else if (distanceX >= 16)	catchUpX = 6.0f;
	else if (distanceX >= 8)	catchUpX = 3.0f;
	else if (distanceX >= 4)	catchUpX = 1.7f;
	else if (distanceX >= 2)	catchUpX = 0.8f;
	else						catchUpX = 0.0f;

	if (distanceY >= 32)		catchUpY = 6.0f;
	else if (distanceY >= 16)	catchUpY = 6.0f;
	else if (distanceY >= 8)	catchUpY = 3.0f;
	else if (distanceY >= 4)	catchUpY = 1.7f;
	else if (distanceY >= 2)	catchUpY = 0.8f;
	else						catchUpY = 0.0f;



	if (_CamPosition.x < _target.x)_CamPosition.x += catchUpX;
	else if (_CamPosition.x > _target.x)_CamPosition.x -= catchUpX;
	if (_CamPosition.y < _target.y)_CamPosition.y += catchUpY;
	else if (_CamPosition.y > _target.y)_CamPosition.y -= catchUpY;




}

