#include "Camera.h"


Camera::Camera() {


	RECT rc = { 0,0,0,0 };
	GetClientRect(hWnd, &rc);


	Pos =	XMFLOAT3(0.0f, 0.0f, -5.0f);
	At =	XMFLOAT3(0.0f, 0.0f, 0.0f);
	Up =	XMFLOAT3(0.0f, 1.0f, 0.0f);



	fov = XMConvertToRadians(45);
	aspectRatio = static_cast<float>(rc.right) / static_cast<float>(rc.bottom);

	nearClip = 0.01f;
	farClip = 1000.0f;

	UpdateCameraMatrix();
	UpdateScreenMatrix();


}

void Camera::UpdateCameraMatrix() {




}
void Camera::UpdateScreenMatrix() {


}


void Camera::Update() {

	UpdateCameraMatrix();
	UpdateScreenMatrix();
	



}
void Camera::Draw() {


}