#include "Camera.h"


Camera::Camera() {


	RECT rc = { 0 };
	GetWindowRect(hWnd, &rc);

	m_screenX = rc.right - rc.left;
	m_screenY = rc.bottom - rc.top;

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

	UpdateUIMatrices();

}

void Camera::UpdateCameraMatrix() {

	XMStoreFloat4x4(&_CameraMatrix,  XMMatrixLookAtLH(XMLoadFloat3(&_CamPosition), XMLoadFloat3(&_CamLookAt), XMLoadFloat3(&_CamUpVector)));

}
void Camera::UpdateScreenMatrix() {
	
	if (_IsCamPerspective) XMStoreFloat4x4(&_ScreenMatrix, XMMatrixPerspectiveFovLH(_CamFOVangle, _CamAspectRatio, _CamNearClip, _CamFarClip));
	else XMStoreFloat4x4(&_ScreenMatrix, XMMatrixOrthographicLH(m_screenX, m_screenY, _CamNearClip, _CamFarClip));


}

void Camera::UpdateCameraScreenMatrix(){

	XMStoreFloat4x4(&_CameraScreenMatrix, GetCameraMatrix() * GetScreenMatrix());

}

void Camera::UpdateAllMatrices(){
	UpdateCameraMatrix();
	UpdateScreenMatrix();
	UpdateCameraScreenMatrix();
}




const XMMATRIX Camera::GetCameraMatrix(){

	return XMLoadFloat4x4(&_CameraMatrix);
}

const XMMATRIX Camera::GetScreenMatrix(){

	return XMLoadFloat4x4(&_ScreenMatrix);

}

const XMMATRIX Camera::GetCameraScreenMatrix() {

	return XMLoadFloat4x4(&_CameraScreenMatrix);
}



// UI Matrices
const XMMATRIX Camera::GetUIScreenMatrix(){
	return XMLoadFloat4x4(&_UIScreenMatix);
}

const XMMATRIX Camera::GetUICameraMatrix(){
	return XMLoadFloat4x4(&_UICameraMatrix);
}

const XMMATRIX	Camera::GetUICameraScreenMatrix() {
	return XMLoadFloat4x4(&_UICameraScreenMatrix);

}
void Camera::UpdateUIMatrices() {
	XMStoreFloat4x4(&_UIScreenMatix, XMMatrixOrthographicLH(m_screenX, m_screenY, 0.01f, 1000.0f));
	XMStoreFloat4x4(&_UICameraMatrix, XMMatrixLookAtLH(XMLoadFloat3(&XMFLOAT3(0.0f, 0.0f, -10.0f)), XMLoadFloat3(&XMFLOAT3(0.0f, 0.0f, 0.0f)), XMLoadFloat3(&XMFLOAT3(0.0f, 1.0f, 0.0f))));
	XMStoreFloat4x4(&_UICameraScreenMatrix, GetUICameraMatrix() * GetUIScreenMatrix());
}
// End UI


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
	
	float t = timer.GetDelta();
	float lerp = 0.005f;

	_CamPosition.x += (_target.x - _CamPosition.x) * lerp * t;
	_CamPosition.y += (_target.y - _CamPosition.y) * lerp * t;

	_CamLookAt.x = _CamPosition.x;
	_CamLookAt.y = _CamPosition.y;
	
	UpdateAllMatrices();



}

