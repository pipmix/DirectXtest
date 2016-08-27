#pragma once
#include "Headers.h"
#include "DataTypes.h"

extern ComPtr<ID3D11Device>			device;
extern ComPtr<ID3D11DeviceContext>	context;


extern HWND hWnd;
extern HINSTANCE hInst;



 class Camera {


	public:

		Camera();
		void Update();
		void Draw();

		void UpdateCameraMatrix();
		void UpdateScreenMatrix();


		XMFLOAT3 Pos;
		XMFLOAT3 At;
		XMFLOAT3 Up;




		float fov;
		float aspectRatio;

		float nearClip;
		float farClip;
};


