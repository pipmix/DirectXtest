#pragma once
#include "Headers.h"
#include "DataTypes.h"

extern ComPtr<ID3D11Device>			device;
extern ComPtr<ID3D11DeviceContext>	context;

extern HWND hWnd;
extern HINSTANCE hInst;


extern XMMATRIX worldMatrix;
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

		ComPtr<ID3D11Buffer>			constantBuffer;


};


