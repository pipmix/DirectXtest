#pragma once
#include "Headers.h"
#include "DataTypes.h"

extern ComPtr<ID3D11Device>			device;
extern ComPtr<ID3D11DeviceContext>	context;
extern ComPtr<ID3D11Buffer>			constantBuffer;

extern HWND hWnd;
extern HINSTANCE hInst;


extern XMMATRIX cameraScreenMatrix;;
extern XMMATRIX cameraMatrix;
extern XMMATRIX screenMatrix;

 class Camera {


	public:

		Camera();
		void Update();
		void Draw();



		//XMFLOAT3					lookAt;
		//XMFLOAT3					up;
		//XMFLOAT3					eye;


		long mWindowWidth;
		long mWidowHeight;



		float fov;
		float aspectRatio;

		float nearClip;
		float farClip;
};


