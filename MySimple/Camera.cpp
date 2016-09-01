#include "Camera.h"


Camera::Camera() {


	RECT rc = { 0,0,0,0 };
	GetClientRect(hWnd, &rc);


	Pos =	XMFLOAT3(0.0f, 0.0f, -15.0f);
	At =	XMFLOAT3(0.0f, 0.0f, 0.0f);
	Up =	XMFLOAT3(0.0f, 1.0f, 0.0f);

	fov = XMConvertToRadians(45);
	aspectRatio = static_cast<float>(rc.right - rc.left) / static_cast<float>(rc.bottom - rc.top);

	nearClip = 0.01f;
	farClip = 1000.0f;

	UpdateCameraMatrix();
	UpdateScreenMatrix();


}

void Camera::UpdateCameraMatrix() {

	cameraMatrix = XMMatrixLookAtLH(XMLoadFloat3(&Pos), XMLoadFloat3(&At), XMLoadFloat3(&Up));

}
void Camera::UpdateScreenMatrix() {

	screenMatrix = XMMatrixPerspectiveFovLH(fov, aspectRatio, nearClip, farClip);;

}


void Camera::Update() {

	UpdateCameraMatrix();
	UpdateScreenMatrix();
	
	cameraScreenMatrix = cameraMatrix * screenMatrix;


}
void Camera::Draw() {


}